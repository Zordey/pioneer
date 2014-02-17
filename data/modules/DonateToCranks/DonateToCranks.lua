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
local Comms = import("Comms")
local Event = import("Event")
local Serializer = import("Serializer")

local l = Lang.GetResource("module-donatetocranks")

local flavours = {}
for i = 0,5 do
	table.insert(flavours, {
		title     = l["FLAVOUR_" .. i .. "_TITLE"],
		message   = l["FLAVOUR_" .. i .. "_MESSAGE"],
	})
end
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

local ads = {}

local onChat = function (form, ref, option)
<<<<<<< HEAD
	local crank_flavours = Translate:GetFlavours('DonateToCranks')
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	local ad = ads[ref]

	if option == 0 then
		form:Clear()

		form:SetTitle(ad.title)
		form:SetFace({ seed = ad.faceseed })
		form:SetMessage(ad.message)

		form:AddOption("$1", 1)
		form:AddOption("$10", 10)
		form:AddOption("$100", 100)
		form:AddOption("$1000", 1000)
		form:AddOption("$10000", 10000)
		form:AddOption("$100000", 100000)
<<<<<<< HEAD
		form:AddOption(t('HANG_UP'), -1)
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

		return
	end

	if option == -1 then
		form:Close()
		return
	end

	if Game.player:GetMoney() < option then
<<<<<<< HEAD
		Comms.Message(t("You do not have enough money."))
	else
		if option >= 10000 then
			Comms.Message(t("Wow! That was very generous."))
		else
			Comms.Message(t("Thank you. All donations are welcome."))
=======
		Comms.Message(l.YOU_DO_NOT_HAVE_ENOUGH_MONEY)
	else
		if option >= 10000 then
			Comms.Message(l.WOW_THAT_WAS_VERY_GENEROUS)
		else
			Comms.Message(l.THANK_YOU_ALL_DONATIONS_ARE_WELCOME)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		end
		Game.player:AddMoney(-option)
	end
end

local onDelete = function (ref)
	ads[ref] = nil
end

local onCreateBB = function (station)
<<<<<<< HEAD
  local crank_flavours = Translate:GetFlavours('DonateToCranks')
	local n = Engine.rand:Integer(1, #crank_flavours)

	local ad = {
		title    = crank_flavours[n].title,
		message  = crank_flavours[n].message,
=======
	local n = Engine.rand:Integer(1, #flavours)

	local ad = {
		title    = flavours[n].title,
		message  = flavours[n].message,
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		station  = station,
		faceseed = Engine.rand:Integer()
	}

	local ref = station:AddAdvert(ad.title, onChat, onDelete)
	ads[ref] = ad
end

local loaded_data

local onGameStart = function ()
	ads = {}

	if not loaded_data then return end

	for k,ad in pairs(loaded_data.ads) do
		local ref = ad.station:AddAdvert(ad.title, onChat, onDelete)
		ads[ref] = ad
	end

	loaded_data = nil
end

local serialize = function ()
	return { ads = ads }
end

local unserialize = function (data)
	loaded_data = data
end

Event.Register("onCreateBB", onCreateBB)
Event.Register("onGameStart", onGameStart)

Serializer:Register("DonateToCranks", serialize, unserialize)
