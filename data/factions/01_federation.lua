local f = Faction:new('Federation')
	:description_short('The historical birthplace of humankind')
	:description([[Sol is a fine joint]])
	:govtype('EARTHDEMOC')
	:homeworld(0,0,0,0,4)
	:foundingDate(3050.0)
	:expansionRate(1.0)
	:military_name('United Nations Space Force')
	:police_name('Police')
	:colour(0.4,0.4,1.0)

f:illegal_goods_probability('ANIMAL_MEAT',25)	-- fed/cis
f:illegal_goods_probability('LIVE_ANIMALS',25)	-- fed/cis
f:illegal_goods_probability('HAND_WEAPONS',0)	-- fed
f:illegal_goods_probability('BATTLE_WEAPONS',50)	--fed/cis
f:illegal_goods_probability('NERVE_GAS',0)--fed/cis
f:illegal_goods_probability('NARCOTICS',0)--fed
f:illegal_goods_probability('SLAVES',0)--fed/cis

f:add_to_factions('Federation')
