<<<<<<< HEAD
-- Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local t = Translate:GetTranslator()

local messages = {
	GRAV_TOO_HIGH    = 'Cannot compensate for local gravity',
	REFUSED_PERM     = 'Starport refused docking permission',
	ORBIT_IMPOSSIBLE = 'Cannot compute orbit parameters',
=======
-- Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local Lang = import("Lang")
local Comms = import("Comms")
local Event = import("Event")

local l = Lang.GetResource("module-aiwarning")

local messages = {
	GRAV_TOO_HIGH    = l.CANNOT_COMPENSATE_FOR_LOCAL_GRAVITY,
	REFUSED_PERM     = l.CANNOT_COMPUTE_ORBIT_PARAMETERS,
	ORBIT_IMPOSSIBLE = l.STARPORT_REFUSED_DOCKING_PERMISSION,
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

Event.Register("onAICompleted", function (s, e)
	if e == 'NONE' then return end
	if not s:IsPlayer() then return end

<<<<<<< HEAD
	Comms.ImportantMessage(t(messages[e]), t('AUTOPILOT'))
=======
	Comms.ImportantMessage(messages[e], l.AUTOPILOT)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
end)
