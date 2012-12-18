-- Copyright © 2008-2012 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

--
-- Class: Missions
--
-- A mission object, which is displayed in the missions screen. These
-- missions are stored in the PersistenCharacters.player.missions table.
-- The class is responsible for inserting itself into the missions table,
-- and has a method which removes itself from that table.
--
-- Lua modules should use the Missions interface, which provides data
-- sanitation and error checking.
--

local MissionStatus = {
	-- Valid mission states, used in data sanitation
	ACTIVE = true,
	COMPLETED = true,
	FAILED = true,
}

-- Registered mission click functions go here
local MissionClickHandler = {}

Mission = {
--
-- Group: Attributes
--

--
-- Attribute: type
--
-- The type of mission.  This can be any translatable string token.
--
-- Availability:
--
--   alpha 30
--
-- Status:
--
--   experimental
--
	type = 'NONE',

--
-- Attribute: client
--
-- The [Character] object that offered the mission
--
-- Availability:
--
--   alpha 30
--
-- Status:
--
--   experimental
--

--
-- Attribute: due
--
-- Due date/time, in seconds since 12:00 01-01-3200
--
-- Availability:
--
--   alpha 30
--
-- Status:
--
--   experimental
--
	due = 0,

--
-- Attribute: reward
--
-- Reward for mission completion, in dollars
--
-- Availability:
--
--   alpha 30
--
-- Status:
--
--   experimental
--
	reward = 0,

--
-- Attribute:Location 
--
-- A [SystemPath] for the destination space station
--
-- Availability:
--
--   alpha 30
--
-- Status:
--
--   experimental
--
	location = nil,

--
-- Attribute: status
--
-- A string for the current mission status. Must be one of 'ACTIVE', 'COMPLETED' or 'FAILED'
--
-- Availability:
--
--   alpha 30
--
-- Status:
--
--   experimental
--
	status = 'ACTIVE',

--
-- Group: Methods
--

--
-- Method: New
--
-- Create a new mission and add it to the player's mission list
--
-- >	missionRef = Mission.New({
-- >		'type'     = type,
-- >		'client'   = client,
-- >		'due'      = due,
-- >		'reward'   = reward,
-- >		'location' = location,
-- >		'status'   = status,
-- >	})
--
-- Parameters:
--
-- New takes a table as its only parameter.  The fields of that table match the attributes
-- of the Mission class.
--
-- Return:
--
--   missionRef - a new instance of the Mission class
--
-- Example:
--
-- >  local ref = Mission.New({
-- >      'type'     = 'Delivery',
-- >      'client'   = Character.New()
-- >      'due'      = Game.time + 3*24*60*60,    -- three days
-- >      'reward'   = 123.45,
-- >      'location' = SystemPath:New(0,0,0,0,16),  -- Mars High, Sol
-- >      'status'   = 'ACTIVE',
-- >  })
--
-- Availability:
--
-- alpha 29
--
-- Status:
--
-- testing
--
	New = function (template)
		-- Data sanitation
		if not template or (type(template) ~= 'table') then
			error("Missing argument: mission table expected")
		end
		local test = getmetatable(template)
		if(test and (test.class == 'Mission')) then
			error("Won't use another mission as a template.")
		end
		if not (type(template.type) == "string") then template.type = nil end
		if not template.client then template.client = Character.New() end
		if not (
			type(template.client) == "table" and
			getmetatable(template.client) and
			getmetatable(template.client).class == 'Character'
		) then
			error("Mission.New: client must be a Character object")
		end
		-- Initialise the new mission
		local newMission = {}
		for k,v in pairs(template) do
			newMission[k] = v
		end
		setmetatable(newMission,Mission.meta)		
		if not (type(newMission.due) == "number") then newMission.due = nil end
		if not (type(newMission.reward) == "number") then newMission.reward = nil end
		if not (type(newMission.location) == "userdata") then newMission.location = Game.system.path end
		table.insert(PersistentCharacters.player.missions,newMission)
		return NewMission;
	end,
--
-- Method: Remove
--
-- Remove a mission from the player's mission list
--
-- Mission:Remove()
--
-- Example:
--
-- > ourMission:Remove() -- Remove mission from list
-- > ourMission = nil    -- Remove our reference too
--
-- Availability:
--
-- alpha 30
--
-- Status:
--
-- testing
--
	Remove = function (self)
		for k,v in pairs(PersistentCharacters.player.missions) do
			if v == self then
				table.remove(PersistentCharacter.player.missions,k)
			end
		end
	end,

--
-- Method: RegisterClick
--
-- Register a handler function for the mission list button
--
-- > Mission.RegisterClick(type, handler)
--
-- Parameters:
--
--   type - the mission type, as seen in the Mission.Add() example
--
--   handler - a function to be run when the "Active" button is
--             clicked. Handler is passed a reference compatible with
--             Mission.Get() and may return an Engine.ui instance, which
--             will be displayed on screen if not nil.
--
-- Example:
--
-- > Mission.RegisterClick('Race',function (ref)
-- >   local race = races[ref] -- Assuming some local table of races for example
-- >   Comms.Message(string.interp('Stage {stage}: You are in position {pos}',{stage=race.stage, pos=race.pos}))
-- > end) -- Not returning a UI in this small example
--
-- Availability:
--
-- alpha 29
--
-- Status:
--
-- experimental
--
	RegisterClick = function (missiontype, handler)
		if not (type(missiontype) == 'string') then
			error('Mission.RegisterClick: type must be a translatable string token')
		end
		if not (type(handler) == 'function') then
			error('Mission.RegisterClick: handler must be a function')
		end
		MissionClickHandler[missiontype] = handler
	end,
--
-- Method: GetClick
--
-- Internal method to retrieve a handler function for the mission list button.
-- Normally called from InfoView/Missions, but could be useful elsewhere.
--
-- > handler = ourMission:GetClick()
--
--
-- Returns:
--
--   handler - a function to be connected to the missions form 'Active'
--             button.
--
-- Availability:
--
-- alpha 29
--
-- Status:
--
-- experimental
--
	GetClick = function (self)
		local t = Translate:GetTranslator()
		return MissionClickHandler[self.type] or function (ref) return Engine.ui:Label(t('NOT_FOUND')) end
	end,

	Serialize = function (self)
		return self
	end,

	Unserialize = function (data)
		setmetatable(data,Mission.meta)
		return data
	end,
}

Mission.meta = {
	__index = Mission,
	class = "Mission",
}
