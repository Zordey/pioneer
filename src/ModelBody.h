<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _MODELBODY_H
#define _MODELBODY_H

#include "libs.h"
#include "Body.h"
<<<<<<< HEAD
#include "vector3.h"
#include "CollMesh.h"
=======
#include "CollMesh.h"
#include "Shields.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

class Geom;
class Camera;
namespace Graphics { class Renderer; class Light; }
<<<<<<< HEAD
namespace SceneGraph { class Model; }
=======
namespace SceneGraph { class Model; class Animation; }
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

class ModelBody: public Body {
public:
	OBJDEF(ModelBody, Body, MODELBODY);
	ModelBody();
	virtual ~ModelBody();
	void SetPosition(const vector3d &p);
	void SetOrient(const matrix3x3d &r);
	void TransformToModelCoords(const Frame *camFrame);
	void SetFrame(Frame *f);
	// Colliding: geoms are checked against collision space
	void SetColliding(bool colliding);
	bool IsColliding() const { return m_colliding; }
	// Static: geoms are static relative to frame
	void SetStatic(bool isStatic);
	bool IsStatic() const { return m_isStatic; }
	const Aabb &GetAabb() const { return m_collMesh->GetAabb(); }
<<<<<<< HEAD
	Geom *GetGeom() { return m_geom; }
	SceneGraph::Model *GetModel() { return m_model; }
	CollMesh *GetCollMesh() { return m_collMesh.Get(); }
	void RebuildCollisionMesh();

	void SetModel(const char *modelName);

	void RenderModel(Graphics::Renderer *r, const Camera *camera, const vector3d &viewCoords, const matrix4x4d &viewTransform, const bool setLighting=true);

=======
	SceneGraph::Model *GetModel() const { return m_model; }
	CollMesh *GetCollMesh() { return m_collMesh.Get(); }

	void SetModel(const char *modelName);

	void RenderModel(Graphics::Renderer *r, const Camera *camera, const vector3d &viewCoords, const matrix4x4d &viewTransform, const bool setLighting=true);

	virtual void TimeStepUpdate(const float timeStep);

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
protected:
	virtual void Save(Serializer::Writer &wr, Space *space);
	virtual void Load(Serializer::Reader &rd, Space *space);

	void SetLighting(Graphics::Renderer *r, const Camera *camera, std::vector<Graphics::Light> &oldLights, Color &oldAmbient);
	void ResetLighting(Graphics::Renderer *r, const std::vector<Graphics::Light> &oldLights, const Color &oldAmbient);

<<<<<<< HEAD
private:
=======
	Shields* GetShields() const { return m_shields.get(); }

private:
	void RebuildCollisionMesh();
	void DeleteGeoms();
	void AddGeomsToFrame(Frame*);
	void RemoveGeomsFromFrame(Frame*);
	void MoveGeoms(const matrix4x4d&, const vector3d&);

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	void CalcLighting(double &ambient, double &direct, const Camera *camera);

	bool m_isStatic;
	bool m_colliding;
	RefCountedPtr<CollMesh> m_collMesh;
<<<<<<< HEAD
	Geom *m_geom;
	std::string m_modelName;
	SceneGraph::Model *m_model;
=======
	Geom *m_geom; //static geom
	std::string m_modelName;
	SceneGraph::Model *m_model;
	std::vector<Geom*> m_dynGeoms;
	SceneGraph::Animation *m_idleAnimation;
	std::unique_ptr<Shields> m_shields;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
};

#endif /* _MODELBODY_H */
