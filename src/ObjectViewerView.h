#ifndef _OBJECTVIEWERVIEW_H
#define _OBJECTVIEWERVIEW_H

//#ifdef DEBUG

#include "libs.h"
#include "Gui.h"
#include "View.h"

class Body;

class ObjectViewerView: public View {
public:
	ObjectViewerView();
	virtual void Update();
	virtual void Draw3D();
	virtual void OnSwitchTo();
private:
	float viewingDist;
	Gui::Label *m_infoLabel;
	const Body* lastTarget;
	matrix4x4d m_camRot;

	Gui::TextEntry *m_sbodyMass;
	Gui::TextEntry *m_sbodyRadius;
	Gui::TextEntry *m_sbodySeed;
	Gui::TextEntry *m_sbodyVolatileGas;
	Gui::TextEntry *m_sbodyVolatileLiquid;
	Gui::TextEntry *m_sbodyVolatileIces;
	Gui::TextEntry *m_sbodyLife;
	Gui::TextEntry *m_sbodyVolcanicity;
	Gui::TextEntry *m_sbodyMetallicity;
	void OnChangeGeoSphereStyle();
};

//#endif

#endif /* _OBJECTVIEWERVIEW_H */
