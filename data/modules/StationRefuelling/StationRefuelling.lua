-- Get the translator function
local t = Translate:GetTranslator()

local minimum_fee = 1
local maximum_fee = 6

local calculateFee = function ()
	local fee = math.ceil(Game.system.population * 3)
	if fee < minimum_fee then
		return minimum_fee
	elseif fee > maximum_fee then
		return maximum_fee
	else
		return fee
	end
end


local onShipDocked = function (ship, station)
	if not ship:IsPlayer() then return end
	local fee = calculateFee()
	if Game.player:GetMoney() < fee then
		UI.Message(t("This is {station}. You do not have enough for your docking fee of {fee}. Your fuel has been witheld."):interp({station = station.label,fee = Format.Money(fee)}))
		Game.player:SetMoney(0)
	else
		UI.Message(t("Welcome aboard {station}. Your docking and fuelling fee of {fee} has been deducted."):interp({station = station.label,fee = Format.Money(fee)}))
		Game.player:AddMoney(0 - fee)
		Game.player:SetFuelPercent()
	end
end

EventQueue.onShipDocked:Connect(onShipDocked)
