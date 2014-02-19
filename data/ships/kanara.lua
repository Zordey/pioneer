<<<<<<< HEAD
-- Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of CC-BY-SA 3.0. See licenses/CC-BY-SA-3.0.txt

define_ship {
	name='Kanara Interceptor',
	model='kanara',
	forward_thrust = 65e5,
	reverse_thrust = 12e5,
	up_thrust = 18e5,
	down_thrust = 18e5,
	left_thrust = 18e5,
	right_thrust = 18e5,
	angular_thrust = 25e5,
--	camera_offset = v(0,4.5,-12.5),
	gun_mounts =
	{
		{ v(0,-2,-46), v(0,0,-1), 5, 'HORIZONTAL' },
		{ v(0,0,0), v(0,0,1), 5, 'HORIZONTAL' },
	},
	max_cargo = 15,
	max_laser = 1,
	max_missile = 4,
=======
-- Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of CC-BY-SA 3.0. See licenses/CC-BY-SA-3.0.txt

define_ship {
	name='Kanara Police Interceptor',
	ship_class='light_fighter',
	manufacturer='mandarava_csepel',
	model='kanara',
	forward_thrust = 6e6,
	reverse_thrust = 2e6,
	up_thrust = 1e6,
	down_thrust = 1e6,
	left_thrust = 1e6,
	right_thrust = 1e6,
	angular_thrust = 25e5,

	hull_mass = 17,
	fuel_tank_mass = 22,
	capacity = 15,
	max_cargo = 9,
	max_laser = 1,
	max_missile = 8,
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	max_cargoscoop = 0,
	max_engine = 0,
	min_crew = 1,
	max_crew = 2,
<<<<<<< HEAD
	capacity = 15,
	hull_mass = 10,
	fuel_tank_mass = 15,
	-- Exhaust velocity Vc [m/s] is equivalent of engine efficiency and depend on used technology. Higher Vc means lower fuel consumption.
	-- Smaller ships built for speed often mount engines with higher Vc. Another way to make faster ship is to increase fuel_tank_mass.
	effective_exhaust_velocity = 59167e3,
	price = 70000,
=======
	-- Exhaust velocity Vc [m/s] is equivalent of engine efficiency and depend on used technology. Higher Vc means lower fuel consumption.
	-- Smaller ships built for speed often mount engines with higher Vc. Another way to make faster ship is to increase fuel_tank_mass.
	effective_exhaust_velocity = 68e5,
	price = 0,
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	hyperdrive_class = 0,
}

