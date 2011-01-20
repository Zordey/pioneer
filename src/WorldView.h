#ifndef _WORLDVIEW_H
#define _WORLDVIEW_H

#include "libs.h"
#include "Gui.h"
#include "View.h"
#include "Render.h"
#include "Serializer.h"

class Body;
class Frame;
struct SBodyPath;

class WorldView: public View {
public:
	WorldView();
	virtual ~WorldView();
	virtual void ShowAll();
	virtual void Update();
	virtual void Draw3D();
	virtual void OnSwitchTo();
	static const float PICK_OBJECT_RECT_SIZE;
	bool GetShowLabels() { return m_labelsOn; }
	void DrawBgStars();
	vector3d GetExternalViewTranslation();
	void ApplyExternalViewRotation(matrix4x4d &m);
	virtual void Save(Serializer::Writer &wr);
	virtual void Load(Serializer::Reader &rd);
	enum CamType { CAM_FRONT, CAM_REAR, CAM_EXTERNAL };
	void SetCamType(enum CamType);
	enum CamType GetCamType() const;
	int GetNumLights() const { return m_numLights; }
	void ToggleTargetActions();
	void GetNearFarClipPlane(float *outNear, float *outFar) const;
	int GetActiveWeapon() const;
	void OnClickBlastoff();

	sigc::signal<void> onChangeCamType;

	float m_externalViewRotX, m_externalViewRotY;
	float m_externalViewDist;

private:
	void RefreshButtonStateAndVisibility();
	void UpdateCommsOptions();
	void DrawHUD(const Frame *cam_frame);
	void DrawTargetSquares();
	void DrawTargetSquare(const Body* const target);
	Gui::Button *AddCommsOption(const std::string msg, int ypos, int optnum);
	void OnClickHyperspace();
	void OnChangeWheelsState(Gui::MultiStateImageButton *b);
	void OnChangeLabelsState(Gui::MultiStateImageButton *b);
	void OnChangeFlightState(Gui::MultiStateImageButton *b);
	void OnChangeHyperspaceTarget();
	void OnPlayerDockOrUndock();
	void OnPlayerChangeFlightControlState();
	virtual bool OnMouseDown(Gui::MouseButtonEvent *e);
	void SelectBody(Body *, bool reselectIsDeselect);
	Body* PickBody(const float screenX, const float screenY) const;
	void MouseButtonDown(int button, int x, int y);
	Gui::ImageButton *m_hyperspaceButton;
	GLuint m_bgstarsVbo;
	Gui::Fixed *m_commsOptions;
	Gui::Label *m_flightStatus, *m_hyperTargetLabel;
	Gui::ImageButton *m_launchButton;
	Gui::MultiStateImageButton *m_wheelsButton;
	Gui::MultiStateImageButton *m_flightControlButton;
	bool m_labelsOn;
	enum CamType m_camType;
	int m_numLights;
	Uint32 m_showTargetActionsTimeout;
	Render::Shader *m_bgStarShader;

	Gui::Label *m_debugInfo, *m_hudVelocity, *m_hudSetSpeed, *m_hudAltitude,
		*m_hudPressure, *m_hudNavTarget, *m_hudCombatTarget,
		*m_hudHyperspaceInfo;

	Gui::MeterBar *m_hudHullTemp, *m_hudWeaponTemp, *m_hudHullIntegrity, *m_hudShieldIntegrity;

	sigc::connection m_onPlayerChangeHyperspaceTargetCon;
	sigc::connection m_onPlayerChangeTargetCon;
	sigc::connection m_onChangeFlightControlStateCon;
	sigc::connection m_onMouseButtonDown;
};

#endif /* _WORLDVIEW_H */
