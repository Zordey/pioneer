<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef AMBIENTSOUNDS_H
#define AMBIENTSOUNDS_H

class AmbientSounds {
public:
	static void Init();
	static void Uninit();
	static void Update();
private:
	static void UpdateForCamType();
};

#endif /* AMBIENTSOUNDS_H */
