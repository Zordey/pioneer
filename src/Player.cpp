#include "Pi.h"
#include "Player.h"
#include "Frame.h"
#include "WorldView.h"
#include "SpaceStationView.h"
#include "Serializer.h"
#include "Sound.h"
#include "ShipCpanel.h"
#include "KeyBindings.h"

Player::Player(ShipType::Type shipType): Ship(shipType)
{
	m_mouseCMov[0] = m_mouseCMov[1] = 0;
	m_flightControlState = CONTROL_MANUAL;
	m_killCount = 0;
	m_knownKillCount = 0;
	UpdateMass();
}

Player::~Player()
{
	assert(this == Pi::player);
	Pi::player = 0;
}

void Player::Save(Serializer::Writer &wr)
{
	Ship::Save(wr);
	wr.Int32(static_cast<int>(m_flightControlState));
	wr.Float(m_setSpeed);
	wr.Int32(m_killCount);
	wr.Int32(m_knownKillCount);
}

void Player::Load(Serializer::Reader &rd)
{
	Pi::player = this;
	Ship::Load(rd);
	m_flightControlState = static_cast<FlightControlState>(rd.Int32());
	m_setSpeed = rd.Float();
	m_killCount = rd.Int32();
	m_knownKillCount = rd.Int32();
}

void Player::OnHaveKilled(Body *guyWeKilled)
{
	if (guyWeKilled->IsType(Object::SHIP)) {
		printf("Well done. you killed some poor fucker\n");
		m_killCount++;
	}
}

bool Player::OnDamage(Object *attacker, float kgDamage)
{
	bool r = Ship::OnDamage(attacker, kgDamage);
	if (!IsDead() && (GetPercentHull() < 25.0f)) {
		Sound::BodyMakeNoise(this, "warning", .5f);
	}
	return r;
}

void Player::SetFlightControlState(enum FlightControlState s)
{
	m_flightControlState = s;
	if (m_flightControlState == CONTROL_AUTOPILOT) {
		AIClearInstructions();
	} else if (m_flightControlState == CONTROL_FIXSPEED) {
		AIClearInstructions();
		m_setSpeed = GetVelocity().Length();
	} else {
		AIClearInstructions();
	}
	Pi::onPlayerChangeFlightControlState.emit();
}

void Player::Render(const vector3d &viewCoords, const matrix4x4d &viewTransform)
{
	if (!IsDead()) Ship::Render(viewCoords, viewTransform);
}

void Player::SetDockedWith(SpaceStation *s, int port)
{
	Ship::SetDockedWith(s, port);
	if (s) {
		if (Pi::CombatRating(m_killCount) > Pi::CombatRating(m_knownKillCount)) {
			Pi::cpan->MsgLog()->ImportantMessage("Pioneering Pilot's Guild", "Well done commander! Your combat rating has improved!");
		}
		m_knownKillCount = m_killCount;

		Pi::SetView(Pi::spaceStationView);
	}
}

void Player::StaticUpdate(const float timeStep)
{
	Body *b;
	vector3d v;

	if (GetFlightState() == Ship::FLYING) {
		switch (m_flightControlState) {
		case CONTROL_FIXSPEED:
			if (Pi::GetView() == Pi::worldView) PollControls();
			b = (GetCombatTarget() ? GetCombatTarget() : GetNavTarget());
			v = vector3d(0, 0, -m_setSpeed);
			if (b) {
				matrix4x4d m;
				GetRotMatrix(m);
				v += m.InverseOf() * b->GetVelocityRelativeTo(this->GetFrame());
			}
			AIAccelToModelRelativeVelocity(v);
			break;
		case CONTROL_MANUAL:
			if (Pi::GetView() == Pi::worldView) PollControls();
			break;
		case CONTROL_AUTOPILOT:
			break;
		}
	}
	Ship::StaticUpdate(timeStep);
		
	/* This wank probably shouldn't be in Player... */
	/* Ship engine noise. less loud inside */
	float v_env = (Pi::worldView->GetCamType() == WorldView::CAM_EXTERNAL ? 1.0f : 0.5f);
	static Sound::Event sndev;
	float volBoth = 0.0f;
	volBoth += 0.5*GetThrusterState(ShipType::THRUSTER_FORWARD);
	volBoth += 0.5*GetThrusterState(ShipType::THRUSTER_REVERSE);
	volBoth += 0.5*GetThrusterState(ShipType::THRUSTER_UP);
	volBoth += 0.5*GetThrusterState(ShipType::THRUSTER_DOWN);
	
	float targetVol[2] = { volBoth, volBoth };
	targetVol[0] += 0.5*GetThrusterState(ShipType::THRUSTER_RIGHT);
	targetVol[1] += 0.5*GetThrusterState(ShipType::THRUSTER_LEFT);

	targetVol[0] = v_env * CLAMP(targetVol[0], 0.0f, 1.0f);
	targetVol[1] = v_env * CLAMP(targetVol[1], 0.0f, 1.0f);
	float dv_dt[2] = { 4.0f, 4.0f };
	if (!sndev.VolumeAnimate(targetVol, dv_dt)) {
		sndev.Play("Thruster_large", 0.0f, 0.0f, Sound::OP_REPEAT);
		sndev.VolumeAnimate(targetVol, dv_dt);
	}
	float angthrust = 0.1f * v_env * Pi::player->GetAngThrusterState().Length();

	static Sound::Event angThrustSnd;
	if (!angThrustSnd.VolumeAnimate(angthrust, angthrust, 5.0f, 5.0f)) {
		angThrustSnd.Play("Thruster_Small", 0.0f, 0.0f, Sound::OP_REPEAT);
		angThrustSnd.VolumeAnimate(angthrust, angthrust, 5.0f, 5.0f);
	}
}

#define MOUSE_CTRL_AREA		10.0f
#define MOUSE_RESTITUTION	0.75f

void Player::PollControls()
{
	int mouseMotion[2];
	double time_accel = Pi::GetTimeAccel();
	double invTimeAccel = 1.0 / time_accel;

	if ((time_accel == 0) || GetDockedWith() || Pi::player->IsDead() ||
	    (GetFlightState() != FLYING)) {
		return;
	}

	/* if flying */
	{
		ClearThrusterState();
		
		vector3f wantAngVel(0.0f);

		if (Pi::MouseButtonState(3)) {
			Pi::GetMouseMotion(mouseMotion);
			m_mouseCMov[0] += mouseMotion[0];
			m_mouseCMov[1] += mouseMotion[1];
			m_mouseCMov[0] = CLAMP(m_mouseCMov[0]*MOUSE_RESTITUTION, -MOUSE_CTRL_AREA, MOUSE_CTRL_AREA);
			m_mouseCMov[1] = CLAMP(m_mouseCMov[1]*MOUSE_RESTITUTION, -MOUSE_CTRL_AREA, MOUSE_CTRL_AREA);
			wantAngVel.y = -m_mouseCMov[0] / MOUSE_CTRL_AREA;
			wantAngVel.x = m_mouseCMov[1] / MOUSE_CTRL_AREA;
		}
		
		if (m_flightControlState == CONTROL_FIXSPEED) {
			if (KeyBindings::increaseSpeed.IsActive()) m_setSpeed += MAX(m_setSpeed*0.05, 1.0);
			if (KeyBindings::decreaseSpeed.IsActive()) m_setSpeed -= MAX(m_setSpeed*0.05, 1.0);
		}

		if (KeyBindings::thrustForward.IsActive()) SetThrusterState(ShipType::THRUSTER_FORWARD, 1.0f);
		if (KeyBindings::thrustBackwards.IsActive()) SetThrusterState(ShipType::THRUSTER_REVERSE, 1.0f);
		if (KeyBindings::thrustUp.IsActive()) SetThrusterState(ShipType::THRUSTER_UP, 1.0f);
		if (KeyBindings::thrustDown.IsActive()) SetThrusterState(ShipType::THRUSTER_DOWN, 1.0f);
		if (KeyBindings::thrustLeft.IsActive()) SetThrusterState(ShipType::THRUSTER_LEFT, 1.0f);
		if (KeyBindings::thrustRight.IsActive()) SetThrusterState(ShipType::THRUSTER_RIGHT, 1.0f);
		
		SetGunState(0,0);
		SetGunState(1,0);
		if (KeyBindings::fireLaser.IsActive() || (Pi::MouseButtonState(1) && Pi::MouseButtonState(3))) {
				SetGunState(Pi::worldView->GetActiveWeapon(), 1);
		}

		if (KeyBindings::yawLeft.IsActive()) wantAngVel.y += 1.0;
		if (KeyBindings::yawRight.IsActive()) wantAngVel.y += -1.0;
		if (KeyBindings::pitchDown.IsActive()) wantAngVel.x += -1.0;
		if (KeyBindings::pitchUp.IsActive()) wantAngVel.x += 1.0;
		if (KeyBindings::rollLeft.IsActive()) wantAngVel.z += 1.0;
		if (KeyBindings::rollRight.IsActive()) wantAngVel.z -= 1.0;


		for (int axis=0; axis<3; axis++) wantAngVel[axis] = CLAMP(wantAngVel[axis], -invTimeAccel, invTimeAccel);
		
		const float angThrustSoftness = KeyBindings::fastRotate.IsActive() ? 10.0 : 50.0;
		
		AIModelCoordsMatchAngVel(wantAngVel, angThrustSoftness);
	}
}

bool Player::SetWheelState(bool down)
{
	static Sound::Event sndev;
	bool did = Ship::SetWheelState(down);
	if (did) {
		sndev.Play(down ? "UC_out" : "UC_in", 1.0f, 1.0f, 0);
	}
	return did;
}

