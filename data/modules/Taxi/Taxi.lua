<<<<<<< HEAD
-- Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

-- Get the translator function
local t = Translate:GetTranslator()
=======
-- Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local Engine = import("Engine")
local Lang = import("Lang")
local Game = import("Game")
local Space = import("Space")
local Comms = import("Comms")
local Event = import("Event")
local Mission = import("Mission")
local NameGen = import("NameGen")
local Format = import("Format")
local Serializer = import("Serializer")
local Character = import("Character")
local EquipDef = import("EquipDef")
local ShipDef = import("ShipDef")
local Ship = import("Ship")
local utils = import("utils")

local InfoFace = import("ui/InfoFace")

-- Get the language resource
local l = Lang.GetResource("module-taxi")
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
-- Get the UI class
local ui = Engine.ui

-- don't produce missions for further than this many light years away
local max_taxi_dist = 40
-- typical time for travel to a system max_taxi_dist away
--	Irigi: ~ 4 days for in-system travel, the rest is FTL travel time
local typical_travel_time = (2.0 * max_taxi_dist + 4) * 24 * 60 * 60
-- typical reward for taxi service to a system max_taxi_dist away
local typical_reward = 75 * max_taxi_dist
-- max number of passengers per trip
local max_group = 10

<<<<<<< HEAD
=======
local num_corporations = 12
local num_pirate_taunts = 4

local flavours = {
	{
		single = false,  -- flavour 0-2 are for groups
		urgency = 0,
		risk = 0.001,
	}, {
		single = false,
		urgency = 0,
		risk = 0,
	}, {
		single = false,
		urgency = 0,
		risk = 0,
	}, {
		single = true,  -- flavour 3- are for single persons
		urgency = 0.13,
		risk = 0.73,
	}, {
		single = true,
		urgency = 0.3,
		risk = 0.02,
	}, {
		single = true,
		urgency = 0.1,
		risk = 0.05,
	}, {
		single = true,
		urgency = 0.02,
		risk = 0.07,
	}, {
		single = true,
		urgency = 0.15,
		risk = 1,
	}, {
		single = true,
		urgency = 0.5,
		risk = 0.001,
	}, {
		single = true,
		urgency = 0.85,
		risk = 0.20,
	}, {
		single = true,
		urgency = 0.9,
		risk = 0.40,
	}, {
		single = true,
		urgency = 1,
		risk = 0.31,
	}, {
		single = true,
		urgency = 0,
		risk = 0.17,
	}
}

-- add strings to flavours
for i = 1,#flavours do
	local f = flavours[i]
	f.adtext     = l["FLAVOUR_" .. i-1 .. "_ADTEXT"]
	f.introtext  = l["FLAVOUR_" .. i-1 .. "_INTROTEXT"]
	f.whysomuch  = l["FLAVOUR_" .. i-1 .. "_WHYSOMUCH"]
	f.howmany    = l["FLAVOUR_" .. i-1 .. "_HOWMANY"]
	f.danger     = l["FLAVOUR_" .. i-1 .. "_DANGER"]
	f.successmsg = l["FLAVOUR_" .. i-1 .. "_SUCCESSMSG"]
	f.failuremsg = l["FLAVOUR_" .. i-1 .. "_FAILUREMSG"]
	f.wherearewe = l["FLAVOUR_" .. i-1 .. "_WHEREAREWE"]
end

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
local ads = {}
local missions = {}
local passengers = 0

local add_passengers = function (group)
	Game.player:RemoveEquip('UNOCCUPIED_CABIN', group)
	Game.player:AddEquip('PASSENGER_CABIN', group)
	passengers = passengers + group
end

local remove_passengers = function (group)
	Game.player:RemoveEquip('PASSENGER_CABIN', group)
	Game.player:AddEquip('UNOCCUPIED_CABIN', group)
	passengers = passengers - group
end

local onChat = function (form, ref, option)
<<<<<<< HEAD
	local taxi_flavours = Translate:GetFlavours('Taxi')
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local ad = ads[ref]

	form:Clear()

	if option == -1 then
		form:Close()
		return
	end

	if option == 0 then
		form:SetFace(ad.client)

		local sys   = ad.location:GetStarSystem()

<<<<<<< HEAD
		local introtext = string.interp(taxi_flavours[ad.flavour].introtext, {
=======
		local introtext = string.interp(flavours[ad.flavour].introtext, {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			name     = ad.client.name,
			cash     = Format.Money(ad.reward),
			system   = sys.name,
			sectorx  = ad.location.sectorX,
			sectory  = ad.location.sectorY,
			sectorz  = ad.location.sectorZ,
			dist     = string.format("%.2f", ad.dist),
		})

		form:SetMessage(introtext)

	elseif option == 1 then
<<<<<<< HEAD
		local corporation = t('CORPORATIONS')[Engine.rand:Integer(1,#(t('CORPORATIONS')))]
		local whysomuch = string.interp(taxi_flavours[ad.flavour].whysomuch, {
=======
		local corporation = l["CORPORATIONS_"..Engine.rand:Integer(1,num_corporations)-1]
		local whysomuch = string.interp(flavours[ad.flavour].whysomuch, {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			corp     = corporation,
		})

		form:SetMessage(whysomuch)

	elseif option == 2 then
<<<<<<< HEAD
		local howmany = string.interp(taxi_flavours[ad.flavour].howmany, {
=======
		local howmany = string.interp(flavours[ad.flavour].howmany, {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			group  = ad.group,
		})

		form:SetMessage(howmany)

	elseif option == 3 then
		local capacity = ShipDef[Game.player.shipId].equipSlotCapacity.CABIN
		if capacity < ad.group or Game.player:GetEquipCount('CABIN', 'UNOCCUPIED_CABIN') < ad.group then
<<<<<<< HEAD
			form:SetMessage(t("You do not have enough cabin space on your ship."))
			form:AddOption(t('HANG_UP'), -1)
=======
			form:SetMessage(l.YOU_DO_NOT_HAVE_ENOUGH_CABIN_SPACE_ON_YOUR_SHIP)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			return
		end

		add_passengers(ad.group)

		form:RemoveAdvertOnClose()

		ads[ref] = nil

		local mission = {
			type	 = "Taxi",
			client	 = ad.client,
			start    = ad.station.path,
			location = ad.location,
			risk	 = ad.risk,
			reward	 = ad.reward,
			due	 = ad.due,
			group	 = ad.group,
			flavour	 = ad.flavour
		}

		table.insert(missions,Mission.New(mission))

<<<<<<< HEAD
		form:SetMessage(t("Excellent."))
		form:AddOption(t('HANG_UP'), -1)

		return
	elseif option == 4 then
		if taxi_flavours[ad.flavour].single == 1 then
			form:SetMessage(t("I must be there before ")..Format.Date(ad.due))
		else
			form:SetMessage(t("We want to be there before ")..Format.Date(ad.due))
		end

	elseif option == 5 then
		form:SetMessage(taxi_flavours[ad.flavour].danger)
	end

	form:AddOption(t("Why so much money?"), 1)
	form:AddOption(t("How many of you are there?"), 2)
	form:AddOption(t("How soon you must be there?"), 4)
	form:AddOption(t("Will I be in any danger?"), 5)
	form:AddOption(t("Could you repeat the original request?"), 0)
	form:AddOption(t("Ok, agreed."), 3)
	form:AddOption(t('HANG_UP'), -1)
=======
		form:SetMessage(l.EXCELLENT)

		return
	elseif option == 4 then
		if flavours[ad.flavour].single then
			form:SetMessage(l.I_MUST_BE_THERE_BEFORE..Format.Date(ad.due))
		else
			form:SetMessage(l.WE_WANT_TO_BE_THERE_BEFORE..Format.Date(ad.due))
		end

	elseif option == 5 then
		form:SetMessage(flavours[ad.flavour].danger)
	end

	form:AddOption(l.WHY_SO_MUCH_MONEY, 1)
	form:AddOption(l.HOW_MANY_OF_YOU_ARE_THERE, 2)
	form:AddOption(l.HOW_SOON_YOU_MUST_BE_THERE, 4)
	form:AddOption(l.WILL_I_BE_IN_ANY_DANGER, 5)
	form:AddOption(l.COULD_YOU_REPEAT_THE_ORIGINAL_REQUEST, 0)
	form:AddOption(l.OK_AGREED, 3)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
end

local onDelete = function (ref)
	ads[ref] = nil
end

local nearbysystems
local makeAdvert = function (station)
	local reward, due, location
<<<<<<< HEAD
	local taxi_flavours = Translate:GetFlavours('Taxi')
	local client = Character.New()
	local flavour = Engine.rand:Integer(1,#taxi_flavours)
	local urgency = taxi_flavours[flavour].urgency
	local risk = taxi_flavours[flavour].risk
	local group = 1
	if taxi_flavours[flavour].single == 0 then
=======
	local client = Character.New()
	local flavour = Engine.rand:Integer(1,#flavours)
	local urgency = flavours[flavour].urgency
	local risk = flavours[flavour].risk
	local group = 1
	if not flavours[flavour].single then
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		group = Engine.rand:Integer(2,max_group)
	end

	if nearbysystems == nil then
		nearbysystems = Game.system:GetNearbySystems(max_taxi_dist, function (s) return #s:GetStationPaths() > 0 end)
	end
	if #nearbysystems == 0 then return end
	location = nearbysystems[Engine.rand:Integer(1,#nearbysystems)]
	local dist = location:DistanceTo(Game.system)
	reward = ((dist / max_taxi_dist) * typical_reward * (group / 2) * (1+risk) * (1+3*urgency) * Engine.rand:Number(0.8,1.2))
	due = Game.time + ((dist / max_taxi_dist) * typical_travel_time * (1.5-urgency) * Engine.rand:Number(0.9,1.1))

	local ad = {
		station		= station,
		flavour		= flavour,
		client		= client,
		location	= location.path,
		dist            = dist,
		due		= due,
		group		= group,
		risk		= risk,
		urgency		= urgency,
		reward		= reward,
		isfemale	= isfemale,
		faceseed	= Engine.rand:Integer(),
	}

<<<<<<< HEAD
	ad.desc = string.interp(taxi_flavours[flavour].adtext, {
=======
	ad.desc = string.interp(flavours[flavour].adtext, {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		system	= location.name,
		cash	= Format.Money(ad.reward),
	})

	local ref = station:AddAdvert(ad.desc, onChat, onDelete)
	ads[ref] = ad
end

local onCreateBB = function (station)
	local num = Engine.rand:Integer(0, math.ceil(Game.system.population))
	for i = 1,num do
		makeAdvert(station)
	end
end

local onUpdateBB = function (station)
<<<<<<< HEAD
	local taxi_flavours = Translate:GetFlavours('Taxi')
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	for ref,ad in pairs(ads) do
		if ad.due < Game.time + 5*60*60*24 then
			ad.station:RemoveAdvert(ref)
		end
	end
	if Engine.rand:Integer(24*60*60) < 60*60 then -- roughly once every day
		makeAdvert(station)
	end
end

local onEnterSystem = function (player)
	if (not player:IsPlayer()) then return end
<<<<<<< HEAD
	local taxi_flavours = Translate:GetFlavours('Taxi')
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	local syspath = Game.system.path

	for ref,mission in pairs(missions) do
<<<<<<< HEAD
		if not mission.status and mission.location:IsSameSystem(syspath) then
			local risk = taxi_flavours[mission.flavour].risk
=======
		if mission.status == "ACTIVE" and mission.location:IsSameSystem(syspath) then

			local risk = flavours[mission.flavour].risk
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			local ships = 0

			local riskmargin = Engine.rand:Number(-0.3,0.3) -- Add some random luck
			if risk >= (1 + riskmargin) then ships = 3
			elseif risk >= (0.7 + riskmargin) then ships = 2
			elseif risk >= (0.5 + riskmargin) then ships = 1
			end

			if ships < 1 and risk > 0 and Engine.rand:Integer(math.ceil(1/risk)) == 1 then ships = 1 end

			-- XXX hull mass is a bad way to determine suitability for role
<<<<<<< HEAD
			local shipdefs = build_array(filter(function (k,def) return def.tag == 'SHIP' and def.hullMass > 10 and def.hullMass <= 200 end, pairs(ShipDef)))
=======
			local shipdefs = utils.build_array(utils.filter(function (k,def) return def.tag == 'SHIP' and def.hullMass > 10 and def.hullMass <= 200 end, pairs(ShipDef)))
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			if #shipdefs == 0 then return end

			local ship

			while ships > 0 do
				ships = ships-1

				if Engine.rand:Number(1) <= risk then
					local shipdef = shipdefs[Engine.rand:Integer(1,#shipdefs)]
					local default_drive = shipdef.defaultHyperdrive

					local max_laser_size = shipdef.capacity - EquipDef[default_drive].mass
<<<<<<< HEAD
					local laserdefs = build_array(filter(
=======
					local laserdefs = utils.build_array(utils.filter(
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
                        function (k,def) return def.slot == 'LASER' and def.mass <= max_laser_size and string.sub(def.id,0,11) == 'PULSECANNON' end,
                        pairs(EquipDef)
                    ))
					local laserdef = laserdefs[Engine.rand:Integer(1,#laserdefs)]

					ship = Space.SpawnShipNear(shipdef.id, Game.player, 50, 100)
<<<<<<< HEAD
=======
					ship:SetLabel(Ship.MakeRandomLabel())
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
					ship:AddEquip(default_drive)
					ship:AddEquip(laserdef.id)
					ship:AddEquip('SHIELD_GENERATOR', math.ceil(risk * 3))
					if Engine.rand:Number(2) <= risk then
						ship:AddEquip('LASER_COOLING_BOOSTER')
					end
					if Engine.rand:Number(3) <= risk then
						ship:AddEquip('SHIELD_ENERGY_BOOSTER')
					end
					ship:AIKill(Game.player)
				end
			end

			if ship then
<<<<<<< HEAD
				local pirate_greeting = string.interp(t('PIRATE_TAUNTS')[Engine.rand:Integer(1,#(t('PIRATE_TAUNTS')))], { client = mission.client.name,})
=======
				local pirate_greeting = string.interp(l["PIRATE_TAUNTS_"..Engine.rand:Integer(1,num_pirate_taunts)-1], { client = mission.client.name,})
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
				Comms.ImportantMessage(pirate_greeting, ship.label)
			end
		end

<<<<<<< HEAD
		if not mission.status and Game.time > mission.due then
			mission.status = 'FAILED'
			Comms.ImportantMessage(taxi_flavours[mission.flavour].wherearewe, mission.client.name)
=======
		if mission.status == "ACTIVE" and Game.time > mission.due then
			mission.status = 'FAILED'
			Comms.ImportantMessage(flavours[mission.flavour].wherearewe, mission.client.name)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		end
	end
end

local onLeaveSystem = function (ship)
	if ship:IsPlayer() then
		nearbysystems = nil
	end
end

local onShipDocked = function (player, station)
	if not player:IsPlayer() then return end

	for ref,mission in pairs(missions) do
		if mission.location == Game.system.path or Game.time > mission.due then
<<<<<<< HEAD
			local taxi_flavours = Translate:GetFlavours('Taxi')

			if Game.time > mission.due then
				Comms.ImportantMessage(taxi_flavours[mission.flavour].failuremsg, mission.client.name)
			else
				Comms.ImportantMessage(taxi_flavours[mission.flavour].successmsg, mission.client.name)
=======
			if Game.time > mission.due then
				Comms.ImportantMessage(flavours[mission.flavour].failuremsg, mission.client.name)
			else
				Comms.ImportantMessage(flavours[mission.flavour].successmsg, mission.client.name)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
				player:AddMoney(mission.reward)
			end

			remove_passengers(mission.group)

			mission:Remove()
			missions[ref] = nil
		end
	end
end

local onShipUndocked = function (player, station)
	if not player:IsPlayer() then return end
	local current_passengers = Game.player:GetEquipCount('CABIN', 'PASSENGER_CABIN')
	if current_passengers >= passengers then return end -- nothing changed, good

	for ref,mission in pairs(missions) do
		remove_passengers(mission.group)

<<<<<<< HEAD
		Comms.ImportantMessage(t("Hey!?! You are going to pay for this!!!"), mission.client.name)
=======
		Comms.ImportantMessage(l.HEY_YOU_ARE_GOING_TO_PAY_FOR_THIS, mission.client.name)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		mission:Remove()
		missions[ref] = nil
	end
end

local loaded_data

local onGameStart = function ()
	ads = {}
	missions = {}
	passengers = 0

	if not loaded_data then return end

	for k,ad in pairs(loaded_data.ads) do
		local ref = ad.station:AddAdvert(ad.desc, onChat, onDelete)
		ads[ref] = ad
	end

	missions = loaded_data.missions
	passengers = loaded_data.passengers

	loaded_data = nil
end

local onGameEnd = function ()
	nearbysystems = nil
end

local onClick = function (mission)
<<<<<<< HEAD
	local taxi_flavours = Translate:GetFlavours('Taxi')
	local dist = Game.system and string.format("%.2f", Game.system:DistanceTo(mission.location)) or "???"
	return ui:Grid(2,1)
		:SetColumn(0,{ui:VBox(10):PackEnd({ui:MultiLineText((taxi_flavours[mission.flavour].introtext):interp({
=======
	local dist = Game.system and string.format("%.2f", Game.system:DistanceTo(mission.location)) or "???"
	return ui:Grid(2,1)
		:SetColumn(0,{ui:VBox(10):PackEnd({ui:MultiLineText((flavours[mission.flavour].introtext):interp({
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
														name   = mission.client.name,
														system = mission.location:GetStarSystem().name,
														sectorx = mission.location.sectorX,
														sectory = mission.location.sectorY,
														sectorz = mission.location.sectorZ,
														cash   = Format.Money(mission.reward),
														dist  = dist})
										),
										ui:Margin(10),
										ui:Grid(2,1)
											:SetColumn(0, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:Label(t("From:"))
=======
													ui:Label(l.FROM)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											})
											:SetColumn(1, {
												ui:VBox():PackEnd({
													ui:MultiLineText(mission.start:GetStarSystem().name.." ("..mission.start.sectorX..","..mission.start.sectorY..","..mission.start.sectorZ..")")
												})
											}),
										ui:Grid(2,1)
											:SetColumn(0, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:Label(t("To:"))
=======
													ui:Label(l.TO)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											})
											:SetColumn(1, {
												ui:VBox():PackEnd({
													ui:MultiLineText(mission.location:GetStarSystem().name.." ("..mission.location.sectorX..","..mission.location.sectorY..","..mission.location.sectorZ..")")
												})
											}),
										ui:Grid(2,1)
											:SetColumn(0, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:Label(t("Group details:"))
=======
													ui:Label(l.GROUP_DETAILS)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											})
											:SetColumn(1, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:MultiLineText(string.interp(taxi_flavours[mission.flavour].howmany, {group = mission.group}))
=======
													ui:MultiLineText(string.interp(flavours[mission.flavour].howmany, {group = mission.group}))
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											}),
										ui:Grid(2,1)
											:SetColumn(0, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:Label(t("Deadline:"))
=======
													ui:Label(l.DEADLINE)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											})
											:SetColumn(1, {
												ui:VBox():PackEnd({
													ui:Label(Format.Date(mission.due))
												})
											}),
										ui:Grid(2,1)
											:SetColumn(0, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:Label(t("Danger:"))
=======
													ui:Label(l.DANGER)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											})
											:SetColumn(1, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:MultiLineText(taxi_flavours[mission.flavour].danger)
=======
													ui:MultiLineText(flavours[mission.flavour].danger)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											}),
										ui:Margin(5),
										ui:Grid(2,1)
											:SetColumn(0, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:Label(t("Distance:"))
=======
													ui:Label(l.DISTANCE)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											})
											:SetColumn(1, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:Label(dist.." "..t("ly"))
=======
													ui:Label(dist.." "..l.LY)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											}),
		})})
		:SetColumn(1, {
<<<<<<< HEAD
			ui:VBox(10):PackEnd(UI.InfoFace.New(mission.client))
=======
			ui:VBox(10):PackEnd(InfoFace.New(mission.client))
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		})
end

local serialize = function ()
	return { ads = ads, missions = missions, passengers = passengers }
end

local unserialize = function (data)
	loaded_data = data
end

Event.Register("onCreateBB", onCreateBB)
Event.Register("onUpdateBB", onUpdateBB)
Event.Register("onEnterSystem", onEnterSystem)
Event.Register("onLeaveSystem", onLeaveSystem)
Event.Register("onShipUndocked", onShipUndocked)
Event.Register("onShipDocked", onShipDocked)
Event.Register("onGameStart", onGameStart)
Event.Register("onGameEnd", onGameEnd)

<<<<<<< HEAD
Mission.RegisterType('Taxi','Taxi',onClick)
=======
Mission.RegisterType('Taxi',l.TAXI,onClick)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

Serializer:Register("Taxi", serialize, unserialize)
