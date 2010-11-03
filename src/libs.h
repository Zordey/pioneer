#ifndef _LIBS_H
#define _LIBS_H

#include <assert.h>
#include <stdio.h>
#include <sigc++/sigc++.h>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_image.h>
#include <float.h>
#include <limits>
#include <time.h>
#include <stdarg.h>

#define DEBUG

/* on unix this would probably become $PREFIX/pioneer */
#ifndef PIONEER_DATA_DIR
#define PIONEER_DATA_DIR "data"
#endif /* PIONEER_DATA_DIR */

#ifdef _WIN32
#include <malloc.h>
#define alloca _alloca
#define strncasecmp strnicmp
#define strcasecmp stricmp
#else
#include <alloca.h>
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#define snprintf _snprintf
#endif

#include "fixed.h"
#include "vector3.h"
#include "Aabb.h"
#include "matrix4x4.h"
#include "Color.h"
#include "mtrand.h"

#include "utils.h"

#ifdef NDEBUG 
#define	PiVerify(x) x
#else
#define PiVerify(x) assert(x)
#endif

#define USE_VBO	GLEW_ARB_vertex_buffer_object
//#define USE_VBO 0

#define UNIVERSE_SEED	0xabcd1234

#define EARTH_RADIUS	6378135.0
#define EARTH_MASS	5.9742e24
#define JUPITER_MASS	(317.8*EARTH_MASS)
// brown dwarfs above 13 jupiter masses fuse deuterium
#define MIN_BROWN_DWARF	(13.0*JUPITER_MASS)
#define SOL_RADIUS	6.955e8
#define SOL_MASS	1.98892e30
#define AU		149598000000.0
#define G		6.67428e-11

#define HUD_ALPHA 0.34f

#define MIN(x,y)        ((x)<(y)?(x):(y))
#define MAX(x,y)        ((x)>(y)?(x):(y))
#define CLAMP(a, min, max)      (((a) > (max)) ? (max) : (((a) < (min)) ? (min) : (a)))
#define DEG_2_RAD	0.0174532925
#define DEG2RAD(x) ((x)*M_PI/180.0)

#endif /* _LIBS_H */
