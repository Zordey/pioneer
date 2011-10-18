#include "Terrain.h"
#include "TerrainNoise.h"
#include "TerrainComponent.h"

using namespace TerrainNoise;
using namespace TerrainComponent;

template <>
double TerrainHeightFractal<TerrainHeightRuggedLava>::GetHeight(const vector3d &p)
{
	double continents = octavenoise(GetFracDef(0), Clamp(0.725-(m_sealevel/2), 0.1, 0.725), p) - m_sealevel;
	if (continents < 0) return 0;
	double mountain_distrib = octavenoise(GetFracDef(1), 0.55, p);
	double mountains = octavenoise(GetFracDef(2), 0.5, p) * ridged_octavenoise(GetFracDef(2), 0.575, p);
	double mountains2 = octavenoise(GetFracDef(3), 0.5, p);
	double hill_distrib = octavenoise(GetFracDef(4), 0.5, p);
	double hills = hill_distrib * GetFracDef(5).amplitude * octavenoise(GetFracDef(5), 0.5, p);
	double rocks = octavenoise(GetFracDef(9), 0.5, p);

	
	double n = continents - (GetFracDef(0).amplitude*m_sealevel);
	//double n = (megavolcano_function(p) + volcano_function(p) + smlvolcano_function(p));
	n += mountains*mountains2*5.0*megavolcano_function(GetFracDef(6), p);
	n += 2.5*megavolcano_function(GetFracDef(6), p);
	n += mountains*mountains2*5.0*volcano_function(GetFracDef(6), p)*volcano_function(GetFracDef(6), p);
	n += 2.5*volcano_function(GetFracDef(6), p);
	
	n += mountains*mountains2*7.5*megavolcano_function(GetFracDef(7), p);
	n += 2.5*megavolcano_function(GetFracDef(7), p);
	n += mountains*mountains2*7.5*volcano_function(GetFracDef(7), p)*volcano_function(GetFracDef(7), p);
	n += 2.5*volcano_function(GetFracDef(7), p);

	
	//n += 1.4*(continents - targ.continents.amplitude*targ.sealevel + (volcano_function(p)*1)) ;
	//smooth canyon transitions and limit height of canyon placement
	if (n < .01) n += n * 100.0f * canyon3_ridged_function(GetFracDef(8), p);
	else if (n < .7) n += canyon3_ridged_function(GetFracDef(8), p);
	else n += canyon3_ridged_function(GetFracDef(8), p);

	if (n < .01) n += n * 100.0f * canyon2_ridged_function(GetFracDef(8), p);
	else if (n < .7) n += canyon2_ridged_function(GetFracDef(8), p);
	else n += canyon2_ridged_function(GetFracDef(8), p);
	n *= 0.5;

	n += continents*hills*hill_distrib*mountain_distrib;

	mountains  = octavenoise(GetFracDef(1), 0.5, p) *
			GetFracDef(2).amplitude * mountains*mountains*mountains;
	mountains2 = octavenoise(GetFracDef(4), 0.5, p) *
			GetFracDef(3).amplitude * mountains2*mountains2*mountains2;
	/*mountains = fractal(2, targ.mountainDistrib, (m_seed>>2)&3, p) *
		targ.mountains.amplitude * mountains*mountains*mountains;
	mountains2 = fractal(24, targ.mountainDistrib, (m_seed>>2)&3, p) *
		targ.mountains.amplitude * mountains*mountains*mountains;*/
		
	n += continents*mountains*hill_distrib ;
	if (n < 0.01) n += continents*mountains2 * n * 40.0f ;
	else n += continents*mountains2*.4f ;
	n *= 0.2;
	n += mountains*mountains2*mountains2*hills*hills*hill_distrib*mountain_distrib*20.0;

	rocks = continents * mountain_distrib * GetFracDef(9).amplitude * rocks*rocks*rocks * 2.0;
	n += rocks;

	n = (n<0.0 ? 0.0 : m_maxHeight*n);
	return n;
}

template <>
void TerrainHeightFractal<TerrainHeightRuggedLava>::InitFracDef(MTRand &rand)
{
}
