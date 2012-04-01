define_ship {
	name='Eagle Long Range Fighter',
	model = 'eagle_lrf',
	forward_thrust = -34e5,
	reverse_thrust = 17e5,
	up_thrust = 8e5,
	down_thrust = -8e5,
	left_thrust = -8e5,
	right_thrust = 8e5,
	angular_thrust = 64e5,
	rear_camera = v(0,5,-10),
	gun_mounts =
	{
		{ v(0,-.7,-40), v(0,0,-1) },
		{ v(0,-.7,25), v(0,0,1) },
	},
	max_cargo = 20,
	max_missile = 2,
	max_fuelscoop = 0,
	max_cargoscoop = 0,
	capacity = 20,
	hull_mass = 10,
	fuel_tank_mass = 5,
	thruster_fuel_use = 0.0001,
	price = 38000,
	hyperdrive_class = 1,
}

define_ship {
	name='Eagle MK-II',
	model = 'eagle_mk2',
	forward_thrust = -34e5,
	reverse_thrust = 17e5,
	up_thrust = 8e5,
	down_thrust = -8e5,
	left_thrust = -8e5,
	right_thrust = 8e5,
	angular_thrust = 64e5,
	rear_camera = v(0,5,-10),
	gun_mounts =
	{
		{ v(0,-.7,-40), v(0,0,-1) },
		{ v(0,-.7,25), v(0,0,1) },
	},
	max_cargo = 22,
	max_missile = 2,
	max_fuelscoop = 0,
	max_cargoscoop = 0,
	capacity = 22,
	hull_mass = 9,
	fuel_tank_mass = 6,
	thruster_fuel_use = 0.0001,
	price = 41000,
	hyperdrive_class = 1,
}

define_ship {
	name='Eagle MK-III',
	model = 'eagle_mk3',
	forward_thrust = -36e5,
	reverse_thrust = 25e5,
	up_thrust = 8e5,
	down_thrust = -8e5,
	left_thrust = -8e5,
	right_thrust = 8e5,
	angular_thrust = 64e5,
	rear_camera = v(0,5,-10),
	gun_mounts =
	{
		{ v(0,-.7,-40), v(0,0,-1) },
		{ v(0,-.7,25), v(0,0,1) },
	},
	max_cargo = 22,
	max_missile = 2,
	max_fuelscoop = 0,
	max_cargoscoop = 0,
	capacity = 22,
	hull_mass = 10,
	fuel_tank_mass = 5,
	thruster_fuel_use = 0.00015,
	price = 43000,
	hyperdrive_class = 1,
}

define_ship {
	name='Eagle MK-IV "Bomber"',
	model='eagle_mk4',
	forward_thrust = -50e5,
	reverse_thrust = 25e5,
	up_thrust = 14e5,
	down_thrust = -12e5,
	left_thrust = -12e5,
	right_thrust = 12e5,
	angular_thrust = 90e5,
	rear_camera = v(0,5,-10),
	gun_mounts =
	{
		{ v(0,-.7,-40), v(0,0,-1) },
		{ v(0,-.7,25), v(0,0,1) },
	},
	max_cargo = 36,
	max_laser = 2,
	max_missile = 6,
	max_fuelscoop = 1,
	max_cargoscoop = 1,
	capacity = 36,
	hull_mass = 15,
	fuel_tank_mass = 5,
	thruster_fuel_use = 0.00015,
	price = 56000,
	hyperdrive_class = 2,
}
