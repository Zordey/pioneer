<<<<<<< HEAD
-- Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
-- Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

-- example of a custom system directly specifying a faction
local s = CustomSystem:new('Rondel',{'STAR_M'})
	:faction('Red')
	:short_desc('Military Listening Post')
	:long_desc([[A hidden dagger pointed at the heart of the Federation]])
	:seed(1824351)

s:add_to_sector(-1,6,2,v(0.007,0.260,0.060))
