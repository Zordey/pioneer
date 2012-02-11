#include "render/Renderer.h"
#include "render/RendererLegacy.h"

/*
 * OpenGL 2.x renderer
 *  - no fixed function support (shaders for everything)
 *  - try to stick to bufferobjects
 *  - avoid glVertexPointer, glColorPointer?
 *
 *  To do: a nice buffer object class
 */
class RendererGL2 : public RendererLegacy // XXX not really desired, just want to get up to speed
{
public:
	RendererGL2(int width, int height);
	virtual ~RendererGL2();

	virtual const char* GetName() { return "GL2 renderer"; }

	virtual bool BeginFrame();

	virtual bool SetPerspectiveProjection(float fov, float aspect, float near, float far);

	virtual bool DrawLines(int vertCount, const LineVertex *vertices, LineType type=LINE_SINGLE);
	virtual bool DrawLines(int vertCount, const vector3f *vertices, const Color &color, LineType type=LINE_SINGLE);
	virtual bool DrawTriangles(const VertexArray *vertices, const Material *material=0, PrimitiveType type=TRIANGLES);

protected:
	virtual void ApplyMaterial(const Material *mat);
	virtual void UnApplyMaterial(const Material *mat);
};