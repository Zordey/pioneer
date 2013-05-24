-- Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of CC-BY-SA 3.0. See licenses/CC-BY-SA-3.0.txt

define_ship {
	name='Venturestar',
	model='venturestar',
	forward_thrust = 35e6,
	reverse_thrust = 10e6,
	up_thrust = 15e6,
	down_thrust = 10e6,
	left_thrust = 10e6,
	right_thrust = 10e6,
	angular_thrust = 20e7,
	camera_offset = v(0,6,-4),
	gun_mounts =
	{
		{ v(0,-0.5,-10.7), v(0,0,-1), 5, 'HORIZONTAL' },
	},
	max_cargo = 500,
	max_laser = 1,
	max_missile = 16,
	max_cargoscoop = 1,
	max_fuelscoop = 1,
	atmoshield = 1,
	min_crew = 3,
	max_crew = 5,
	capacity = 500,
	hull_mass = 200,
	fuel_tank_mass = 200,
	--thruster_fuel_use = 0.0001,
	effective_exhaust_velocity = 52784e4,
	price = 930000,
	hyperdrive_class = 4,
}
