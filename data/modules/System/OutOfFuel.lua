<<<<<<< HEAD
-- Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local t = Translate:GetTranslator()
=======
-- Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local Lang = import("Lang")
local Comms = import("Comms")
local Event = import("Event")

local l = Lang.GetResource("module-system")
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

local onShipFuelChanged = function (ship, state)
	if ship:IsPlayer() then
		if state == "WARNING" then
<<<<<<< HEAD
			Comms.ImportantMessage(t('Your fuel tank is almost empty.'))
		elseif state == "EMPTY" then
			Comms.ImportantMessage(t('Your fuel tank is empty.'))
=======
			Comms.ImportantMessage(l.YOUR_FUEL_TANK_IS_ALMOST_EMPTY)
		elseif state == "EMPTY" then
			Comms.ImportantMessage(l.YOUR_FUEL_TANK_IS_EMPTY)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		end
	else
		if state == "EMPTY" then
			print(('{label} ({id}) out of fuel'):interp({label=ship.label,id=ship.shipId}))
		end
	end
end

Event.Register("onShipFuelChanged", onShipFuelChanged)
