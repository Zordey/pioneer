<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "LuaObject.h"
#include "Random.h"

/*
 * Class: Rand
 *
 * Class for a random number generator.
 */

/*
 * Function: New
 *
 * Creates a new random number generator.
 *
<<<<<<< HEAD
 * > rand = Rand:New(seed)
=======
 * > rand = Rand.New(seed)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
 *
 * Parameters:
 *
 *   seed - optional, the value to seed the generator with. If omitted it will
<<<<<<< HEAD
 *          be set to the current system (not game) time
=======
 *          be set to the current system (not game) time. seed must be numeric
 *          if given.
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
 *
 * Return:
 *
 *   rand - the newly-created generator
 *
 * Availability:
 *
 *   alpha 10
 *
 * Status:
 *
 *   stable
 */
static int l_rand_new(lua_State *l)
{
	int seed = int(time(0));
<<<<<<< HEAD
	if (lua_isnumber(l, 1))
		seed = lua_tointeger(l, 1);
=======
	if (!lua_isnoneornil(l, 1)) {
		if (lua_isnumber(l, 1))
			seed = lua_tointeger(l, 1);
		else
			luaL_error(l, "seed must be numeric if given");
	}
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	LuaObject<Random>::PushToLua(new Random(seed));
	return 1;
}

/*
 * Method: Number
 *
 * Generates a real (non-integer) number.
 *
 * > number = rand:Number()
 * > number = rand:Number(max)
 * > number = rand:Number(min, max)
 *
 * Parameters:
 *
 *   min - optional, the minimum possible value for the generated number. If
 *         omitted, defaults to 0
 *
 *   max - optional, the maximum possible value for the generated number. If
 *         omitted, defaults to a very large number (currently 2^32-1)
 *
 * Return:
 *
 *   number - the random number
 *
 * Availability:
 *
 *   alpha 10
 *
 * Status:
 *
 *   stable
 */
static int l_rand_number(lua_State *l)
{
	Random *rand = LuaObject<Random>::CheckFromLua(1);

	double min, max;
	if (lua_isnumber(l, 2) && lua_isnumber(l, 3)) {
		min = lua_tonumber(l, 2);
		max = lua_tonumber(l, 3);
	}
	else if (lua_isnumber(l, 2)) {
		min = 0.0;
		max = lua_tonumber(l, 2);
	}
	else {
        lua_pushnumber(l, rand->Double());
        return 1;
	}

	if (min > max)
		luaL_error(l, "Max must be bigger than min in random number range");

	lua_pushnumber(l, rand->Double(min, max));
	return 1;
}

/*
<<<<<<< HEAD
=======
 * Method: Normal
 *
 * Generates a random number drawn from a Gaussian distribution.
 *
 * > number = rand:Normal()
 * > number = rand:Normal(mean)
 * > number = rand:Normal(mean, stddev)
 *
 * Parameters:
 *
 *   mean - optional, the mean (center) of the distribution. If omitted, defaults to 0.
 *
 *   stddev - optional, the standard deviation (width) of the distribution. If
 *            omitted, defaults to 1.
 *
 * Return:
 *
 *   number - the random number
 *
 * Availability:
 *
 *   January 2014
 *
 * Status:
 *
 *   Experimental
 */
static int l_rand_normal(lua_State *l)
{
	Random *rand = LuaObject<Random>::CheckFromLua(1);

	double mean, stddev;
	if (lua_isnumber(l, 2) && lua_isnumber(l, 3)) {
		mean = lua_tonumber(l, 2);
		stddev = lua_tonumber(l, 3);
	}
	else if (lua_isnumber(l, 2)) {
		mean = lua_tonumber(l, 2);
		stddev = 1;
	}
	else {
        lua_pushnumber(l, rand->Normal());
        return 1;
	}

	if (stddev < 0)
		luaL_error(l, "Standard deviation should not be negative.");

	lua_pushnumber(l, rand->Normal(mean, stddev));
	return 1;
}

/*
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
 * Method: Integer
 *
 * Generates an integer number
 *
 * > number = rand:Integer()
 * > number = rand:Integer(max)
 * > number = rand:Integer(min, max)
 *
 * Parameters:
 *
 *   min - optional, the minimum possible value for the generated number. If
 *         omitted, defaults to 0
 *
 *   max - optional, the maximum possible value for the generated number. If
 *         omitted, defaults to a very large number (currently 2^32-1)
 *
 * Return:
 *
 *   number - the random number
 *
 * Availability:
 *
 *   alpha 10
 *
 * Status:
 *
 *   stable
 */
static int l_rand_integer(lua_State *l)
{
	Random *rand = LuaObject<Random>::CheckFromLua(1);

	int min, max;
	if (lua_isnumber(l, 2) && lua_isnumber(l, 3)) {
		min = lua_tointeger(l, 2);
		max = lua_tointeger(l, 3);
	}
	else if (lua_isnumber(l, 2)) {
		min = 0;
		max = lua_tointeger(l, 2);
	}
	else {
        lua_pushnumber(l, rand->Int32());
        return 1;
	}

	if (min > max)
		luaL_error(l, "Max must be bigger than min in random number range");

	lua_pushnumber(l, rand->Int32(min, max));
	return 1;
}

template <> const char *LuaObject<Random>::s_type = "Rand";

template <> void LuaObject<Random>::RegisterClass()
{
	static const luaL_Reg l_methods[] = {
		{ "New",     l_rand_new     },
		{ "Number",  l_rand_number  },
<<<<<<< HEAD
=======
		{ "Normal",  l_rand_normal  },
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		{ "Integer", l_rand_integer },
		{ 0, 0 }
	};

	LuaObjectBase::CreateClass(s_type, 0, l_methods, 0, 0);
}
