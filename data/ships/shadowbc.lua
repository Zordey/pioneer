-- Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of CC-BY-SA 3.0. See licenses/CC-BY-SA-3.0.txt

define_static_ship {
	name='Shadow battle crab',
	model='shadowbc',
	forward_thrust = 60e8,
	reverse_thrust = 40e8,
	up_thrust = 40e8,
	down_thrust = 20e8,
	left_thrust = 20e8,
	right_thrust = 20e8,
	angular_thrust = 60e8,
	camera_offset = v(0,0,0),
	gun_mounts =
	{
		{ v(0,-0.5,-10.7), v(0,0,-1), 5, 'HORIZONTAL' },
	},
	max_cargo = 5000,
	max_laser = 1,
	max_missile = 0,
	max_cargoscoop = 0,
	max_fuelscoop = 0,
	min_crew = 1,
	max_crew = 1,
	capacity = 5000,
	hull_mass = 100,
	fuel_tank_mass = 100,
	--thruster_fuel_use = 0.0001,
	effective_exhaust_velocity = 59167e3,
	price = 43000000,
	hyperdrive_class = 10,
}
