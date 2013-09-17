-- Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of CC-BY-SA 3.0. See licenses/CC-BY-SA-3.0.txt

define_ship {
	name='AC33 (Dropstar)',
	model='AC33',
	forward_thrust = 60e6,
	reverse_thrust = 10e6,
	up_thrust = 15e6,
	down_thrust = 8e6,
	left_thrust = 8e6,
	right_thrust = 8e6,
	angular_thrust = 70e6,
	camera_offset = v(0,0,-18),
	gun_mounts =
	{
		{ v(0,-0.5,-10.7), v(0,0,-1), 5, 'HORIZONTAL' },
	},
	max_cargo = 300,
	max_laser = 1,
	max_missile = 12,
	max_cargoscoop = 0,
	max_fuelscoop = 0,
	min_atmoshield = 1,
	atmoshield = 1,
	min_crew = 1,
	max_crew = 2,
	capacity = 300,
	hull_mass = 400,
	fuel_tank_mass = 50,
	hyperdrive_class = 0,
	effective_exhaust_velocity = 97840e3,
	price = 850000,

}
