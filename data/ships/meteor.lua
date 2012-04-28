define_ship {
	name='Meteor',
	model='meteor',
	forward_thrust = -28e5,
	reverse_thrust = 2e5,
	up_thrust = 5e5,
	down_thrust = -5e5,
	left_thrust = -5e5,
	right_thrust = 5e5,
	angular_thrust = 10e5,
	gun_mounts =
	{
		{ v(0,0,-25), v(0,0,-1) },
	},
	max_cargo = 5,
	max_laser = 1,
	max_missile = 4,
	max_fuelscoop = 1,
	max_cargoscoop = 0,
	max_ecm = 0,
	max_engine = 0,
	hyperdrive_class = 1,
	capacity = 12,
	hull_mass = 5,
	fuel_tank_mass = 7,
	thruster_fuel_use = 0.0005,
	price = 18000,
}
