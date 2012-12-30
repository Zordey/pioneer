-- Copyright © 2008-2012 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of CC-BY-SA 3.0. See licenses/CC-BY-SA-3.0.txt

define_ship {
	name = 'Imperial Courier',
	model = 'courier',
	forward_thrust = 50e6,
	reverse_thrust = 15e6,
	up_thrust = 15e6,
	down_thrust = 8e6,
	left_thrust = 8e6,
	right_thrust = 8e6,
	angular_thrust = 110e6,
	camera_offset = v(0,3.5,-25),
	gun_mounts =
	{
		{ v(0,0.6,-25), v(0,0,-1), 5, 'HORIZONTAL' },
		{ v(0,0,16), v(0,0,1), 5, 'HORIZONTAL' },
	},
	max_cargo = 300,
	max_laser = 1,
	max_missile = 6,
	max_cargoscoop = 0,
	min_crew = 1,
	max_crew = 3,
	capacity = 300,
	hull_mass = 200,
	fuel_tank_mass = 100,
	thruster_fuel_use = 0.0002,
	price = 611000,
	hyperdrive_class = 4,
}
