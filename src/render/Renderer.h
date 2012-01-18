#ifndef _RENDERER_H
#define _RENDERER_H

#include "libs.h"
#include "vector3.h"
#include "Color.h"

/*
 * Draws points, lines, polys...
 * Terrains and LMRmodels might be too special for this now
 * Would ideally also:
 * create and destroy context
 * toggle between fullscreen/windowed
 * prepare/endframe (move from Render.h)
 */

//first some data structures
struct LineVertex {
	LineVertex() : position(0.f, 0.f, 0.f), color(0.f, 0.f, 0.f, 0.f) { }
	LineVertex(const vector3f& v, const Color &c) : position(v), color(c) { }
	vector3f position;
	Color color;
};

enum LineType {
	LINE_SINGLE = GL_LINES, //draw one line per two vertices
	LINE_STRIP = GL_LINE_STRIP,  //connect vertices
	LINE_LOOP = GL_LINE_LOOP    //connect vertices,  connect start & end
};

class Renderer
{
public:
	//drawing functions
	//return false if failed/unsupported
	bool DrawLines(int vertCount, const LineVertex *vertices, unsigned int lineType=LINE_SINGLE);
};

#endif
