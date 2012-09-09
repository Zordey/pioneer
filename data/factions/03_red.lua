local f = Faction:new('Red')
	:description_short('Not Blue')
	:description('The RED team are not Blue')	
	:govtype('EMPIRERULE')
	:homeworld(4,-9,-16,0,16)
	:foundingDate(3150.0)
	:expansionRate(3.0)
	:military_name('Red Fleet')
	:police_name('Red Right Hands')
	
f:illegal_goods_probability('LIQUOR',8,1)	-- independent/empire
f:illegal_goods_probability('HAND_WEAPONS',2,0)	-- empire/etc
f:illegal_goods_probability('BATTLE_WEAPONS',0,0)	--empire/etc
f:illegal_goods_probability('NERVE_GAS',10,0)--empire
f:illegal_goods_probability('NARCOTICS',2,0)--empire
f:illegal_goods_probability('SLAVES',16,0)--empire

f:add_to_factions('Red')
