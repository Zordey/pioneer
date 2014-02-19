<<<<<<< HEAD
-- Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

=======
-- Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local Engine = import("Engine")
local Game = import("Game")
local Space = import("Space")
local Event = import("Event")
local Serializer = import("Serializer")
local ShipDef = import("ShipDef")
local Ship = import("Ship")
local utils = import("utils")

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
local loaded

local spawnShips = function ()
	local population = Game.system.population

	if population == 0 then
		return
	end

	local stations = Space.GetBodies(function (body) return body:isa("SpaceStation") and not body.isGroundStation end)
	if #stations == 0 then
		return
	end

<<<<<<< HEAD
	local shipdefs = build_array(filter(function (k,def) return def.tag == 'STATIC_SHIP' end, pairs(ShipDef)))
=======
	local shipdefs = utils.build_array(utils.filter(function (k,def) return def.tag == 'STATIC_SHIP' end, pairs(ShipDef)))
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	if #shipdefs == 0 then return end

	-- one ship per three billion, min 1, max 2*num of stations
	local num_bulk_ships = math.min(#stations*2, math.floor((math.ceil(population)+2)/3))

	for i=1, num_bulk_ships do
	local station = stations[Engine.rand:Integer(1,#stations)]
<<<<<<< HEAD
		Space.SpawnShipParked(shipdefs[Engine.rand:Integer(1,#shipdefs)].id, station)
=======
		local ship = Space.SpawnShipParked(shipdefs[Engine.rand:Integer(1,#shipdefs)].id, station)
		ship:SetLabel(Ship.MakeRandomLabel())
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	end
end

local onEnterSystem = function (player)
	if not player:IsPlayer() then return end

	spawnShips()
end

local onGameStart = function ()
	if loaded == nil then
		spawnShips()
	end
	loaded = nil
end

local serialize = function ()
	return true
end

local unserialize = function (data)
	loaded = true
end

Event.Register("onEnterSystem", onEnterSystem)
Event.Register("onGameStart", onGameStart)

Serializer:Register("BulkShips", serialize, unserialize)
