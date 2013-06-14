wave = function()
	print('Configuring your Wave Hypersonic Fighter')
	Game.player:SetShipType('wave')
	Game.player:SetLabel('Zordey')
	Game.player:RemoveEquip('DRIVE_CLASS2')
	Game.player:AddEquip('DRIVE_MIL3')
	Game.player:AddEquip('MILITARY_FUEL',10)
	Game.player:AddEquip('AUTOPILOT')
	Game.player:AddEquip('SCANNER')
	Game.player:AddEquip('ATMOSPHERIC_SHIELDING')
	print('Done')

end

deneb = function()
	print('Configuring your Deneb Transport')
	Game.player:SetShipType('deneb')
	Game.player:SetLabel('Zordey')
	Game.player:RemoveEquip('DRIVE_CLASS3')
	Game.player:AddEquip('DRIVE_MIL4')
	Game.player:AddEquip('MILITARY_FUEL',50)
	Game.player:AddEquip('AUTOPILOT')
	Game.player:AddEquip('SCANNER')
	Game.player:AddEquip('ATMOSPHERIC_SHIELDING')
	Game.player:AddEquip('PULSECANNON_DUAL_1MW')
	Game.player:AddEquip('MISSILE_GUIDED',8)
	print('Done')

end	

venturestar = function()
	print('Configuring your Venturestar')
	Game.player:SetShipType('venturestar')
	Game.player:SetLabel('Zordey')
	Game.player:RemoveEquip('DRIVE_CLASS4')
	Game.player:AddEquip('DRIVE_MIL4')
	Game.player:AddEquip('MILITARY_FUEL',50)
	Game.player:AddEquip('AUTOPILOT')
	Game.player:AddEquip('SCANNER')
	Game.player:AddEquip('ATMOSPHERIC_SHIELDING')
	Game.player:AddEquip('PULSECANNON_DUAL_1MW')
	Game.player:AddEquip('MISSILE_GUIDED',16)
	print('Done')

end

lwp = function()
	print('Configuring your Light Weapons Platform')
	Game.player:SetShipType('lwp')
	Game.player:SetLabel('Zordey')
	Game.player:AddEquip('MISSILE_GUIDED',2)
	Game.player:AddEquip('PULSECANNON_DUAL_1MW')
	print('Done')

end

shadowbc = function()
	print('Configuring your Shadow battle crab')
	Game.player:SetShipType('shadowbc')
	Game.player:SetLabel('Zordey')
	Game.player:AddEquip('LARGE_PLASMA_ACCEL')
	Game.player:RemoveEquip('DRIVE_CLASS4')
	Game.player:AddEquip('DRIVE_MIL4')
	Game.player:AddEquip('MILITARY_FUEL',50)
	Game.player:AddEquip('AUTOPILOT')
	Game.player:AddEquip('SCANNER')
	Game.player:AddEquip('ATMOSPHERIC_SHIELDING')
	print('Done')

end

getship = function(shipname)
	print('Configuring your ', shipname)
 	local p = Game.player
 	p:SetShipType(shipname)
 	p:SetLabel('Zordey')
 	p:AddEquip('AUTOPILOT')
 	p:AddEquip('ATMOSPHERIC_SHIELDING') 
 	p:AddEquip('SCANNER')
 	print('Done')

end 

refuel = function(amount)
	print('Refueling')
	local p = Game.player
	p:AddEquip('MILITARY_FUEL',amount)
end

