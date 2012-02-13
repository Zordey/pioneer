#ifndef _RENDERER_LEGACY_H
#define _RENDERER_LEGACY_H

#include "Renderer.h"

// Fixed function renderer
class RendererLegacy : public Renderer
{
public:
	RendererLegacy(int width, int height);
	virtual ~RendererLegacy();

	virtual const char* GetName() { return "Legacy renderer"; }
	virtual bool GetNearFarRange(float &near, float &far) const;

	virtual bool BeginFrame();
	virtual bool EndFrame();
	virtual bool SwapBuffers();

	virtual bool ClearScreen();
	virtual bool ClearDepthBuffer();
	virtual bool SetClearColor(const Color &c);

	virtual bool SetTransform(const matrix4x4d &m);
	virtual bool SetTransform(const matrix4x4f &m);
	virtual bool SetPerspectiveProjection(float fov, float aspect, float near, float far);
	virtual bool SetOrthographicProjection(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);

	virtual bool SetBlendMode(BlendMode mode);

	virtual bool SetLights(int numlights, const Light *l);
	virtual bool SetAmbientColor(const Color &c);

	virtual bool DrawLines(int vertCount, const LineVertex *vertices, LineType lineType=LINE_SINGLE);
	virtual bool DrawLines(int vertCount, const vector3f *vertices, const Color &color, LineType type=LINE_SINGLE);
	virtual bool DrawLines2D(int vertCount, const vector2f *vertices, const Color &color, LineType type=LINE_SINGLE);
	virtual bool DrawPoints(int count, const vector3f *points, const Color *colors, float pointSize=1.f);
	virtual bool DrawPoints2D(int count, const vector2f *points, const Color *colors, float pointSize=1.f);
	virtual bool DrawTriangles(const VertexArray *vertices, const Material *material=0, PrimitiveType type=TRIANGLES);
	virtual bool DrawSurface(const Surface *surface);
	virtual bool DrawPointSprites(int count, const vector3f *positions, const Material *material, float size);
	virtual bool DrawStaticMesh(StaticMesh *thing);

protected:
	virtual void ApplyMaterial(const Material *mat);
	virtual void UnApplyMaterial(const Material *mat);
	//figure out states from a vertex array and enable them
	//also sets vertex pointers
	virtual void EnableClientStates(const VertexArray *v);
	//disable previously enabled
	virtual void DisableClientStates();
	int m_numLights;
	std::vector<GLenum> m_clientStates;
	virtual bool BufferStaticMesh(StaticMesh *m);
	float m_minZNear;
	float m_maxZFar;
};

#endif