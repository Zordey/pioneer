-- Danger should be from 0 to 1. zero means nothing bad happens. greater than
-- zero means spawn an enemy ship of that 'power' to kill you
local delivery_flavours = {
	{
		adtext = "GOING TO the %s system? Money paid for delivery of a small package.",
		introtext = "Hi, I'm %s. I'll pay you %s if you will deliver a small package to %s in the %s (%s, %s) system.",
		whysomuchdoshtext = "When a friend visited me she left behind some clothes and antique paper books. I'd like to have them returned to her.",
		successmsg = "Thank you for the delivery. You have been paid in full.",
		failuremsg = "Jesus wept, you took forever over that delivery. I'm not willing to pay you.",
		danger = 0,
		time = 3,
		money = .5,
	}, {
		adtext = "WANTED. Delivery of a package to the %s system.",
		introtext = "Hello. I'm %s. I'm willing to pay %s for a ship to carry a package to %s in the %s (%s, %s) system.",
		whysomuchdoshtext = "It is nothing special.",
		successmsg = "The package has been received and you have been paid in full.",
		failuremsg = "I'm frustrated by the late delivery of my package, and I refuse to pay you.",
		danger = 0,
		time = 1,
		money = 1,
	}, {
		adtext = "URGENT. Fast ship needed to deliver a package to the %s system.",
		introtext = "Hello. I'm %s. I'm willing to pay %s for a ship to carry a package to %s in the %s (%s, %s) system.",
		whysomuchdoshtext = "It is a research proposal and must be delivered by the deadline or we may not get funding.",
		successmsg = "You have been paid in full for the delivery. Thank you.",
		failuremsg = "I was quite clear about the deadline and am very disappointed by the late delivery. You will not be paid.",
		danger = 0,
		time = .75,
		money = 1.1,
	}, {
		adtext = "DELIVERY. Documents to the %s system. %s to an experienced pilot.",
		introtext = "Hello. I'm %s. I'm willing to pay %s for a ship to carry a package to %s in the %s (%s, %s) system.",
		whysomuchdoshtext = "Some extremely sensitive documents have fallen into my hands, and I have reason to believe that the leak has been traced to me.",
		successmsg = "Your timely and discrete service is much appreciated. You have been paid in full.",
		failuremsg = "Useless! I will never depend on you again! Needless to say, you will not be paid for this.",
		danger = 0.5,
		time = 0.75,
		money = 2.5,
	}
}

--for i = 0,10 do
--	local sys = StarSystem:new(i,2,0)
--	print('Looking near ' .. sys:GetSectorX() .. '/' .. sys:GetSectorY() .. '/' .. sys:GetSystemNum())
--	print(sys:GetSystemName())
--	print(sys:GetSystemShortDescription())
--	local sport = sys:GetRandomStarportNearButNotIn()
--	if sport then
--		print(sport:GetBodyName() .. ' in the ' .. sport:GetSystemName() .. ' system')
--	else
--		print("No suitable nearby space station found.")
--	end
--end

local ads = {}
local missions = {}

local onActivate = function (ref)
end

local onDelete = function (ref)
end

local makeAdvert = function (station)
	local dest = Pi.GetCurrentSystem():GetRandomStarportNearButNotIn()
	if not dest then return end

	local isfemale = Pi.rand:Int(0, 1) == 1
	local client = Pi.rand:PersonName(isfemale)

	local flavour = Pi.rand:Int(1, #delivery_flavours)

	local ad = {
		id       = #ads+1,
		station  = station,
		flavour  = flavour,
		client   = client,
		dest     = dest,
		due      = Pi.GetGameTime() + Pi.rand:Real(0, delivery_flavours[flavour].time * 60*60*24*31),
		reward   = Pi.rand:Real(200, 1000) * delivery_flavours[flavour].money,
	}

	local desc = string.format(delivery_flavours[flavour].adtext, dest:GetName(), format_money(ad.reward))

	local ref = station:AddAdvert(desc, onActivate, onDelete)
	ads[ref] = ad
end

local onCreateBB = function (station)
	for i = 1,10 do --Pi.rand:Int(0, 5) do
		makeAdvert(station)
	end
end

local onUpdateBB = function (station)
end

local onEnterSystem = function (sys, player)
end

local onPlayerDocked = function (station, player)
end

EventQueue.onCreateBB:Connect(onCreateBB)
EventQueue.onUpdateBB:Connect(onUpdateBB)
EventQueue.onEnterSystem:Connect(onEnterSystem)
EventQueue.onPlayerDocked:Connect(onPlayerDocked)

--[[
	GetPlayerMissions = function(self)
		return self.missions
	end,
--]]

--[[
	onCreateBB = function(self, args)
	end,

	onEnterSystem = function(self)
		for k,mission in pairs(self.missions) do
			if mission.status == 'active' and
			   mission.dest:GetSystem() == Pi:GetCurrentSystem() then

				local danger = delivery_flavours[mission.flavour].danger
				if danger > 0 then
					--ship, e = Pi.SpawnShip(Pi.GetGameTime()+60, "Ladybird Starfighter")
					ship, e = Pi.SpawnRandomShip(Pi.GetGameTime(), danger, 20, 100)
					if e == nil then
						ship:ShipAIDoKill(Pi.GetPlayer());
						Pi.ImportantMessage(ship:GetLabel(), _("You're going to regret dealing with %1!", {mission.client}))
					end
				end
			end
		end
	end,

	onPlayerDock = function(self)
		local station = Pi.GetPlayer():GetDockedWith():GetSBody()
		--print('player docked with ' .. station:GetBodyName())
		for k,mission in pairs(self.missions) do
			if mission.status == 'active' then
				if mission.dest == station then
					if Pi.GetGameTime() > mission.due then
						Pi.ImportantMessage(mission.client, delivery_flavours[mission.flavour].failuremsg)
						mission.status = 'failed'
					else
						Pi.ImportantMessage(mission.client, delivery_flavours[mission.flavour].successmsg)
						Pi.GetPlayer():AddMoney(mission.reward)
						mission.status = 'completed'
					end
				elseif Pi.GetGameTime() > mission.due then
					mission.status = 'failed'
				end
			end
		end
	end,
	
	onUpdateBB = function(self, args)
		local station = args[1]
		for k,ad in pairs(self.ads) do
			if (ad.bb == station) and (ad.due < Pi.GetGameTime() + 60*60*24*1) then
				self.ads[k] = nil
				ad.bb:SpaceStationRemoveAdvert(self.__name, ad.id)
			end	
		end
		if Pi.rand:Int(0,12*60*60) < 60*60 then -- roughly once every twelve hours
			self:_TryAddAdvert(station)
		end
	end,
	
	onChatBB = function(self, dialog, optionClicked)
		local ad = self.ads[dialog:GetAdRef()]
		dialog:Clear()
		if optionClicked == -1 then
			dialog:Close()
			return
		elseif optionClicked == 0 then
			dialog:SetMessage(_(delivery_flavours[ad.flavour].introtext, {
				ad.client, format_money(ad.reward), ad.dest:GetBodyName(), ad.dest:GetSystemName(), ad.dest:GetSectorX(), ad.dest:GetSectorY() }))
		elseif optionClicked == 1 then
			dialog:SetMessage(delivery_flavours[ad.flavour].whysomuchdoshtext)
		elseif optionClicked == 2 then
			dialog:SetMessage(_('It must be delivered by %1', { Date.Format(ad.due) }))
		elseif optionClicked == 3 then
			dialog:RemoveAdvertOnClose()
			self.ads[ad.id] = nil
			ad.description = _("Deliver a package to %1 in the %2 system (%3, %4).",
					{ ad.dest:GetBodyName(), ad.dest:GetSystemName(), ad.dest:GetSectorX(), ad.dest:GetSectorY() })
			ad.status = "active"
			table.insert(self.missions, ad)
			dialog:SetMessage("Excellent.")
			dialog:AddOption("Hang up.", -1)
			return
		end
		dialog:AddOption("Why so much money?", 1);
		dialog:AddOption("Could you repeat the original request?", 0);
		dialog:AddOption("How soon must it be delivered?", 2);
		dialog:AddOption("Ok, agreed.", 3);
		dialog:AddOption("Hang up.", -1);
	end,
}
--]]
