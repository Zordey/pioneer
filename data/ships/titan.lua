-- Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of CC-BY-SA 3.0. See licenses/CC-BY-SA-3.0.txt

define_ship {
	name='Titan',
	model='titan',
	forward_thrust = 35e9,
	reverse_thrust = 10e9,
	up_thrust = 15e9,
	down_thrust = 10e9,
	left_thrust = 10e9,
	right_thrust = 10e9,
	angular_thrust = 20e9,
	camera_offset = v(0,6,-4),
	gun_mounts =
	{
		{ v(0,-0.5,-10.7), v(0,0,-1), 5, 'HORIZONTAL' },
	},
	max_cargo = 100000,
	max_laser = 1,
	max_missile = 16,
	max_cargoscoop = 1,
	max_fuelscoop = 1,
	atmoshield = 1,
	min_crew = 3,
	max_crew = 5,
	capacity = 100000,
	hull_mass = 1000,
	fuel_tank_mass = 2000,
	--thruster_fuel_use = 0.0001,
	effective_exhaust_velocity = 52784e4,
	price = 930000,
	hyperdrive_class = 9,
}
