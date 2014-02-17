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
local Timer = import("Timer")
local Event = import("Event")
local Mission = import("Mission")
local Rand = import("Rand")
local NameGen = import("NameGen")
local Character = import("Character")
local Format = import("Format")
local Serializer = import("Serializer")
local EquipDef = import("EquipDef")
local ShipDef = import("ShipDef")
local Ship = import("Ship")
local utils = import("utils")

local InfoFace = import("ui/InfoFace")

local l = Lang.GetResource("module-assassination")

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
-- Get the UI class
local ui = Engine.ui

-- don't produce missions for further than this many light years away
local max_ass_dist = 30

<<<<<<< HEAD
=======
local flavours = {}
for i = 0,5 do
	table.insert(flavours, {
		adtext      = l["FLAVOUR_" .. i .. "_ADTEXT"],
		introtext   = l["FLAVOUR_" .. i .. "_INTROTEXT"],
		successmsg  = l["FLAVOUR_" .. i .. "_SUCCESSMSG"],
		failuremsg  = l["FLAVOUR_" .. i .. "_FAILUREMSG"],
		failuremsg2 = l["FLAVOUR_" .. i .. "_FAILUREMSG2"],
	})
end
local num_titles = 25

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
local ads = {}
local missions = {}

local onDelete = function (ref)
	ads[ref] = nil
end

local onChat = function (form, ref, option)
<<<<<<< HEAD
	local ass_flavours = Translate:GetFlavours('Assassination')
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local ad = ads[ref]

	form:Clear()

	if option == -1 then
		form:Close()
		return
	elseif option == 0 then
		form:SetFace(ad.client)
		local sys = ad.location:GetStarSystem()

<<<<<<< HEAD
		local introtext = string.interp(ass_flavours[ad.flavour].introtext, {
=======
		local introtext = string.interp(flavours[ad.flavour].introtext, {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			name	= ad.client.name,
			cash	= Format.Money(ad.reward),
			target	= ad.target,
			system	= sys.name,
		})
		form:SetMessage(introtext)

	elseif option == 1 then
		local sys = ad.location:GetStarSystem()
		local sbody = ad.location:GetSystemBody()

<<<<<<< HEAD
		form:SetMessage(string.interp(t("{target} will be leaving {spaceport} in the {system} system ({sectorX}, {sectorY}, {sectorZ}), distance {dist} ly, at {date}. The ship is {shipname} and has registration id {shipregid}."), {
=======
		form:SetMessage(string.interp(l.X_WILL_BE_LEAVING, {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		  target    = ad.target,
		  spaceport = sbody.name,
		  system    = sys.name,
		  sectorX   = ad.location.sectorX,
		  sectorY   = ad.location.sectorY,
		  sectorZ   = ad.location.sectorZ,
		  dist      = string.format("%.2f", ad.dist),
		  date      = Format.Date(ad.due),
		  shipname  = ad.shipname,
		  shipregid = ad.shipregid,
		  })
		)

	elseif option == 2 then
		local sbody = ad.location:GetSystemBody()

<<<<<<< HEAD
		form:SetMessage(string.interp(t("It must be done after {target} leaves {spaceport}. Do not miss this opportunity."), {
=======
		form:SetMessage(string.interp(l.IT_MUST_BE_DONE_AFTER, {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		  target    = ad.target,
		  spaceport = sbody.name,
      })
    )

	elseif option == 3 then
		local backstation = Game.player:GetDockedWith().path

		form:RemoveAdvertOnClose()

		ads[ref] = nil

		local mission = {
			type		= "Assassination",
			backstation	= backstation,
			client		= ad.client,
			danger		= ad.danger,
			due		= ad.due,
			flavour		= ad.flavour,
			location	= ad.location,
			reward		= ad.reward,
			shipid		= ad.shipid,
			shipname	= ad.shipname,
			shipregid	= ad.shipregid,
			status		= 'ACTIVE',
			target		= ad.target,
		}

		table.insert(missions,Mission.New(mission))

<<<<<<< HEAD
		form:SetMessage(t("Excellent."))
		form:AddOption(t('HANG_UP'), -1)

		return
	elseif option == 4 then
		form:SetMessage(t("Return here on the completion of the contract and you will be paid."))
	end
	form:AddOption(string.interp(t("Where can I find {target}?"), {target = ad.target}), 1);
	form:AddOption(t("Could you repeat the original request?"), 0);
	form:AddOption(t("How soon must it be done?"), 2);
	form:AddOption(t("How will I be paid?"), 4);
	form:AddOption(t("Ok, agreed."), 3);
	form:AddOption(t('HANG_UP'), -1);
end

local RandomShipRegId = function ()
	local letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	local a = Engine.rand:Integer(1, #letters)
	local b = Engine.rand:Integer(1, #letters)
	return string.format("%s%s-%04d", letters:sub(a,a), letters:sub(b,b), Engine.rand:Integer(0, 9999))
=======
		form:SetMessage(l.EXCELLENT)

		return
	elseif option == 4 then
		form:SetMessage(l.RETURN_HERE_ON_THE_COMPLETION_OF_THE_CONTRACT_AND_YOU_WILL_BE_PAID)
	end
	form:AddOption(string.interp(l.WHERE_CAN_I_FIND_X, {target = ad.target}), 1);
	form:AddOption(l.COULD_YOU_REPEAT_THE_ORIGINAL_REQUEST, 0);
	form:AddOption(l.HOW_SOON_MUST_IT_BE_DONE, 2);
	form:AddOption(l.HOW_WILL_I_BE_PAID, 4);
	form:AddOption(l.OK_AGREED, 3);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
end

local nearbysystems
local makeAdvert = function (station)
<<<<<<< HEAD
	local ass_flavours = Translate:GetFlavours('Assassination')
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	if nearbysystems == nil then
		nearbysystems = Game.system:GetNearbySystems(max_ass_dist, function (s) return #s:GetStationPaths() > 0 end)
	end
	if #nearbysystems == 0 then return end
	local client = Character.New()
	local targetIsfemale = Engine.rand:Integer(1) == 1
<<<<<<< HEAD
	local target = t('TITLE')[Engine.rand:Integer(1, #t('TITLE'))] .. " " .. NameGen.FullName(targetIsfemale)
	local flavour = Engine.rand:Integer(1, #ass_flavours)
=======
	local target = l["TITLE_"..Engine.rand:Integer(1, num_titles)-1] .. " " .. NameGen.FullName(targetIsfemale)
	local flavour = Engine.rand:Integer(1, #flavours)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local nearbysystem = nearbysystems[Engine.rand:Integer(1,#nearbysystems)]
	local nearbystations = nearbysystem:GetStationPaths()
	local location = nearbystations[Engine.rand:Integer(1,#nearbystations)]
	local dist = location:DistanceTo(Game.system)
	local time = Engine.rand:Number(0.3, 3)
	local due = Game.time + Engine.rand:Number(7*60*60*24, time * 31*60*60*24)
	local danger = Engine.rand:Integer(1,4)
	local reward = Engine.rand:Number(2100, 7000) * danger

	-- XXX hull mass is a bad way to determine suitability for role
<<<<<<< HEAD
	--local shipdefs = build_array(filter(function (k,def) return def.tag == 'SHIP' and def.hullMass >= (danger * 17) and def.equipSlotCapacity.ATMOSHIELD > 0 end, pairs(ShipDef)))
	local shipdefs = build_array(filter(function (k,def) return def.tag == 'SHIP' and def.defaultHyperdrive ~= 'NONE' and def.equipSlotCapacity.ATMOSHIELD > 0 end, pairs(ShipDef)))
=======
	--local shipdefs = utils.build_array(utils.filter(function (k,def) return def.tag == 'SHIP' and def.hullMass >= (danger * 17) and def.equipSlotCapacity.ATMOSHIELD > 0 end, pairs(ShipDef)))
	local shipdefs = utils.build_array(utils.filter(function (k,def) return def.tag == 'SHIP' and def.defaultHyperdrive ~= 'NONE' and def.equipSlotCapacity.ATMOSHIELD > 0 end, pairs(ShipDef)))
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local shipdef = shipdefs[Engine.rand:Integer(1,#shipdefs)]
	local shipid = shipdef.id
	local shipname = shipdef.name

	local ad = {
		client = client,
		danger = danger,
		due = due,
		faceseed = Engine.rand:Integer(),
		flavour = flavour,
		isfemale = isfemale,
		location = location,
		dist = dist,
		reward = reward,
		shipid = shipid,
		shipname = shipname,
<<<<<<< HEAD
		shipregid = RandomShipRegId(),
=======
		shipregid = Ship.MakeRandomLabel(),
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		station = station,
		target = target,
	}

<<<<<<< HEAD
	ad.desc = string.interp(ass_flavours[ad.flavour].adtext, {
=======
	ad.desc = string.interp(flavours[ad.flavour].adtext, {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		target	= ad.target,
		system	= nearbysystem.name,
	})
	local ref = station:AddAdvert(ad.desc, onChat, onDelete)
	ads[ref] = ad
end

local onCreateBB = function (station)
	local num = Engine.rand:Integer(0, math.ceil(Game.system.population) / 2 + 1)
	for i = 1,num do
		makeAdvert(station)
	end
end

local onShipHit = function (ship, attacker)
	if attacker and not attacker:IsPlayer() then return end -- XX

	-- When the player attacks the target, make it fight back
	for k,mission in pairs(missions) do
		if mission.status == 'ACTIVE' and
		   mission.ship == ship then
			ship:AIKill(attacker)
			return
		end
	end
end

local onShipDestroyed = function (ship, body)
	for ref, mission in pairs(missions) do
		if mission.status == 'ACTIVE' and
		   mission.ship == ship and
		   mission.due < Game.time then
			if not body:isa("Ship") or
			   not body:IsPlayer() then
				mission.status = 'FAILED'
				mission.notplayer = 'TRUE'
			else -- well done, comrade
				mission.status = 'COMPLETED'
				mission.location = mission.backstation
				mission.notplayer = 'FALSE'
			end
			mission.ship = nil
			return
		end
	end
end

local _setupHooksForMission = function (mission)
	if mission.ship:exists() and
	   mission.due > Game.time then
		-- Target hasn't launched yet. set up a timer to do this
		Timer:CallAt(mission.due, function () if mission.ship:exists() then mission.ship:Undock()
			mission.timer = nil end end)
		mission.timer = 'SET'
	end
end

local planets
local onEnterSystem = function (ship)
	if not ship:IsPlayer() then return end

	local syspath = Game.system.path

	for ref,mission in pairs(missions) do
		if mission.status == 'ACTIVE' then
			if not mission.ship then
				if mission.due > Game.time then
					if mission.location:IsSameSystem(syspath) then -- spawn our target ship
						local station = Space.GetBody(mission.location.bodyIndex)
						local shiptype = ShipDef[mission.shipid]
						local default_drive = shiptype.defaultHyperdrive
<<<<<<< HEAD
						local laserdefs = build_array(filter(function (k,def) return def.slot == 'LASER' end, pairs(EquipDef)))
=======
						local laserdefs = utils.build_array(utils.filter(function (k,def) return def.slot == 'LASER' end, pairs(EquipDef)))
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
						local laserdef = laserdefs[mission.danger]
						local count = tonumber(string.sub(default_drive, -1)) ^ 2

						mission.ship = Space.SpawnShipDocked(mission.shipid, station)
						if mission.ship == nil then
							return -- TODO
						end
						mission.ship:SetLabel(mission.shipregid)
						mission.ship:AddEquip('ATMOSPHERIC_SHIELDING')
						mission.ship:AddEquip(default_drive)
						mission.ship:AddEquip(laserdef.id)
						mission.ship:AddEquip('SHIELD_GENERATOR', mission.danger)
						mission.ship:AddEquip('HYDROGEN', count)
						if mission.danger > 2 then
							mission.ship:AddEquip('SHIELD_ENERGY_BOOSTER')
						end
						if mission.danger > 3 then
							mission.ship:AddEquip('LASER_COOLING_BOOSTER')
						end
						_setupHooksForMission(mission)
						mission.shipstate = 'docked'
					end
				else	-- too late
					mission.status = 'FAILED'
				end
			else
				if not mission.ship:exists() then
					mission.ship = nil
					if mission.due < Game.time then
						mission.status = 'FAILED'
					end
				end
			end
		end
	end
end

local onLeaveSystem = function (ship)
	if ship:IsPlayer() then
		nearbysystems = nil
		planets = nil
	end
end

local onShipDocked = function (ship, station)
	for ref,mission in pairs(missions) do
		if ship:IsPlayer() then
			if mission.status == 'COMPLETED' and
			   mission.backstation == station.path then
<<<<<<< HEAD
				local ass_flavours = Translate:GetFlavours('Assassination')
				local text = string.interp(ass_flavours[mission.flavour].successmsg, {
=======
				local text = string.interp(flavours[mission.flavour].successmsg, {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
					target	= mission.target,
					cash	= Format.Money(mission.reward),
				})
				Comms.ImportantMessage(text, mission.client.name)
				ship:AddMoney(mission.reward)
				mission:Remove()
				missions[ref] = nil
			elseif mission.status == 'FAILED' then
<<<<<<< HEAD
				local ass_flavours = Translate:GetFlavours('Assassination')
				local text
				if mission.notplayer == 'TRUE' then
					text = string.interp(ass_flavours[mission.flavour].failuremsg2, {
						target	= mission.target,
					})
				else
					text = string.interp(ass_flavours[mission.flavour].failuremsg, {
=======
				local text
				if mission.notplayer == 'TRUE' then
					text = string.interp(flavours[mission.flavour].failuremsg2, {
						target	= mission.target,
					})
				else
					text = string.interp(flavours[mission.flavour].failuremsg, {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
						target	= mission.target,
					})
				end
				Comms.ImportantMessage(text, mission.client.name)
				mission:Remove()
				missions[ref] = nil
			end
		else
			if mission.ship == ship then
				mission.status = 'FAILED'
			end
		end
		return
	end
end

local onShipUndocked = function (ship, station)
	if ship:IsPlayer() then return end -- not interested in player, yet

	for ref,mission in pairs(missions) do
		if mission.status == 'ACTIVE' and
		   mission.ship == ship then
			planets = Space.GetBodies(function (body) return body:isa("Planet") end)
			if #planets == 0 then
				ship:AIFlyTo(station)
				mission.shipstate = 'outbound'
			else
				local planet = Engine.rand:Integer(1,#planets)

				mission.ship:AIEnterMediumOrbit(planets[planet])
				mission.shipstate = 'flying'

				table.remove(planets, planet)
			end
			return
		end
	end
end

local onAICompleted = function (ship, ai_error)
	for ref,mission in pairs(missions) do
		if mission.status == 'ACTIVE' and
		   mission.ship == ship then
			if mission.shipstate == 'outbound' then
<<<<<<< HEAD
				local stats = ship:GetStats()
				local systems = Game.system:GetNearbySystems(stats.hyperspaceRange, function (s) return #s:GetStationPaths() > 0 end)
=======
				local systems = Game.system:GetNearbySystems(ship.hyperspaceRange, function (s) return #s:GetStationPaths() > 0 end)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
				if #systems == 0 then return end
				local system = systems[Engine.rand:Integer(1,#systems)]

				mission.shipstate = 'inbound'
				ship:HyperspaceTo(system.path)
			-- the only other states are flying and inbound, and there is no AI to complete for inbound
			elseif ai_error == 'NONE' then
				Timer:CallAt(Game.time + 60 * 60 * 8, function ()
					if mission.ship:exists() then
						local stations = Space.GetBodies(function (body) return body:isa("SpaceStation") end)
						if #stations == 0 then return end
						local station = stations[Engine.rand:Integer(1,#stations)]

						mission.ship:AIDockWith(station)
					end
				end)
			else
				if #planets > 0 then
					local planet = Engine.rand:Integer(1,#planets)

					mission.ship:AIEnterMediumOrbit(planets[planet])

					table.remove(planets, planet)
				else
					mission.ship:AIFlyTo(Space.GetBody(mission.location.bodyIndex))
					mission.shipstate = 'outbound'
				end
			end
		end
	end
end

local onUpdateBB = function (station)
	for ref,ad in pairs(ads) do
		if (ad.due < Game.time + 5*60*60*24) then
			ad.station:RemoveAdvert(ref)
		end
	end
	if Engine.rand:Integer(4*24*60*60) < 60*60 then -- roughly once every four days
		makeAdvert(station)
	end
end

local loaded_data

local onGameStart = function ()
	ads = {}
	missions = {}

	if not loaded_data then return end

	for k,ad in pairs(loaded_data.ads) do
		local ref = ad.station:AddAdvert(ad.desc, onChat, onDelete)
		ads[ref] = ad
	end

	missions = loaded_data.missions

	loaded_data = nil
end

local onGameEnd = function ()
	nearbysystems = nil
end

local onClick = function (mission)
<<<<<<< HEAD
	local ass_flavours = Translate:GetFlavours('Assassination')
	local dist = Game.system and string.format("%.2f", Game.system:DistanceTo(mission.location)) or "???"
	return ui:Grid(2,1)
		:SetColumn(0,{ui:VBox(10):PackEnd({ui:MultiLineText((ass_flavours[mission.flavour].introtext):interp({
=======
	local dist = Game.system and string.format("%.2f", Game.system:DistanceTo(mission.location)) or "???"
	return ui:Grid(2,1)
		:SetColumn(0,{ui:VBox(10):PackEnd({ui:MultiLineText((flavours[mission.flavour].introtext):interp({
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
														name   = mission.client.name,
														target = mission.target,
														system = mission.location:GetStarSystem().name,
														cash   = Format.Money(mission.reward),
														dist  = dist})
										),
										ui:Margin(10),
										ui:Grid(2,1)
											:SetColumn(0, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:Label(t("Target name:"))
=======
													ui:Label(l.TARGET_NAME)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											})
											:SetColumn(1, {
												ui:VBox():PackEnd({
													ui:MultiLineText(mission.target)
												})
											}),
										ui:Grid(2,1)
											:SetColumn(0, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:Label(t("Spaceport:"))
=======
													ui:Label(l.SPACEPORT)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											})
											:SetColumn(1, {
												ui:VBox():PackEnd({
													ui:MultiLineText(mission.location:GetSystemBody().name)
												})
											}),
										ui:Grid(2,1)
											:SetColumn(0, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:Label(t("System:"))
=======
													ui:Label(l.SYSTEM)
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
													ui:Label(t("Ship:"))
=======
													ui:Label(l.SHIP)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											})
											:SetColumn(1, {
												ui:VBox():PackEnd({
													ui:MultiLineText(mission.shipname)
												})
											}),
										ui:Grid(2,1)
											:SetColumn(0, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:Label(t("Ship ID:"))
=======
													ui:Label(l.SHIP_ID)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											})
											:SetColumn(1, {
												ui:VBox():PackEnd({
													ui:Label(mission.shipregid),
												})
											}),
										ui:Grid(2,1)
											:SetColumn(0, {
												ui:VBox():PackEnd({
<<<<<<< HEAD
													ui:MultiLineText(t("Target will be leaving spaceport at:"))
=======
													ui:MultiLineText(l.TARGET_WILL_BE_LEAVING_SPACEPORT_AT)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
												})
											})
											:SetColumn(1, {
												ui:VBox():PackEnd({
													ui:Label(Format.Date(mission.due))
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
	return { ads = ads, missions = missions }
end

local unserialize = function (data)
	loaded_data = data
	for k,mission in pairs(loaded_data.missions) do
		if mission.ship and
		   mission.ship:exists() and
		   mission.timer == 'SET' then
			Timer:CallAt(mission.due, function () if mission.ship:exists() then mission.ship:Undock()
				mission.timer = nil end end)
		end
	end
end

Event.Register("onCreateBB", onCreateBB)
Event.Register("onGameStart", onGameStart)
Event.Register("onEnterSystem", onEnterSystem)
Event.Register("onLeaveSystem", onLeaveSystem)
Event.Register("onShipDestroyed", onShipDestroyed)
Event.Register("onShipUndocked", onShipUndocked)
Event.Register("onAICompleted", onAICompleted)
Event.Register("onShipDocked", onShipDocked)
Event.Register("onShipHit", onShipHit)
Event.Register("onUpdateBB", onUpdateBB)
Event.Register("onGameEnd", onGameEnd)

<<<<<<< HEAD
Mission.RegisterType('Assassination','Assassination',onClick)
=======
Mission.RegisterType('Assassination',l.ASSASSINATION,onClick)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

Serializer:Register("Assassination", serialize, unserialize)
