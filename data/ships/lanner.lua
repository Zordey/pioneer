-- Copyright © 2008-2012 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of CC-BY-SA 3.0. See COPYING.txt for details

define_ship {
	name='Lanner',
	model='lanner_ub',
	forward_thrust = -30e6,
	reverse_thrust = 10e6,
	up_thrust = 10e6,
	down_thrust = -5e6,
	left_thrust = -5e6,
	right_thrust = 5e6,
	angular_thrust = 90e6,
	gun_mounts =
	{
	{v(0,-1.9,-38), v(0,0,-1)},
	{v(0,1,38), v(0,0,1)},
	},
	max_cargo = 190,
	max_laser = 2,
	max_missile = 4,
	max_cargoscoop = 0,
	capacity = 190,
	hull_mass = 130,
	fuel_tank_mass = 60,
	thruster_fuel_use = 0.00025,
	price = 280000,
	hyperdrive_class = 3,
}
