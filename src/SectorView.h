<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _SECTORVIEW_H
#define _SECTORVIEW_H

#include "libs.h"
#include "gui/Gui.h"
#include "View.h"
#include <vector>
#include <set>
#include <string>
#include "View.h"
#include "galaxy/Sector.h"
#include "galaxy/SystemPath.h"
#include "graphics/Drawables.h"

class SectorView: public View {
public:
	SectorView();
	SectorView(Serializer::Reader &rd);
	virtual ~SectorView();

	virtual void Update();
	virtual void ShowAll();
	virtual void Draw3D();
	vector3f GetPosition() const { return m_pos; }
	SystemPath GetSelectedSystem() const { return m_selected; }
	SystemPath GetHyperspaceTarget() const { return m_hyperspaceTarget; }
	void SetHyperspaceTarget(const SystemPath &path);
	void FloatHyperspaceTarget();
	void ResetHyperspaceTarget();
	void GotoSector(const SystemPath &path);
	void GotoSystem(const SystemPath &path);
	void GotoCurrentSystem() { GotoSystem(m_current); }
	void GotoSelectedSystem() { GotoSystem(m_selected); }
	void GotoHyperspaceTarget() { GotoSystem(m_hyperspaceTarget); }
	virtual void Save(Serializer::Writer &wr);

	sigc::signal<void> onHyperspaceTargetChanged;

protected:
	virtual void OnSwitchTo();
private:
	void InitDefaults();
	void InitObject();

<<<<<<< HEAD
	struct SystemLabels {
		Gui::Label *systemName;
		Gui::Label *distance;
=======
	struct DistanceIndicator {
		Gui::Label *label;
		Graphics::Drawables::Line3D *line;
		Color okayColor;
		Color unsuffFuelColor;
		Color outOfRangeColor;
	};

	struct SystemLabels {
		Gui::Label *systemName;
		Gui::Label *sector;
		DistanceIndicator distance;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		Gui::Label *starType;
		Gui::Label *shortDesc;
	};

<<<<<<< HEAD
	void DrawNearSectors(matrix4x4f modelview);
	void DrawNearSector(int x, int y, int z, const vector3f &playerAbsPos, const matrix4x4f &trans);
	void PutSystemLabels(Sector *sec, const vector3f &origin, int drawRadius);

	void DrawFarSectors(matrix4x4f modelview);
=======
	void DrawNearSectors(const matrix4x4f& modelview);
	void DrawNearSector(const int sx, const int sy, const int sz, const vector3f &playerAbsPos, const matrix4x4f &trans);
	void PutSystemLabels(Sector *sec, const vector3f &origin, int drawRadius);

	void DrawFarSectors(const matrix4x4f& modelview);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	void BuildFarSector(Sector *sec, const vector3f &origin, std::vector<vector3f> &points, std::vector<Color> &colors);
	void PutFactionLabels(const vector3f &secPos);

	void SetSelectedSystem(const SystemPath &path);
	void OnClickSystem(const SystemPath &path);

<<<<<<< HEAD
=======
	void UpdateDistanceLabelAndLine(DistanceIndicator &distance, const SystemPath &src, const SystemPath &dest);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	void UpdateSystemLabels(SystemLabels &labels, const SystemPath &path);
	void UpdateFactionToggles();
	void RefreshDetailBoxVisibility();

	void UpdateHyperspaceLockLabel();

<<<<<<< HEAD
	Sector* GetCached(const SystemPath& loc);
	Sector* GetCached(const int sectorX, const int sectorY, const int sectorZ);
	void ShrinkCache();

	void MouseButtonDown(int button, int x, int y);
	void OnKeyPressed(SDL_keysym *keysym);
	void OnSearchBoxKeyPress(const SDL_keysym *keysym);
=======
	void MouseWheel(bool up);
	void OnKeyPressed(SDL_Keysym *keysym);
	void OnSearchBoxKeyPress(const SDL_Keysym *keysym);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	bool m_inSystem;

	SystemPath m_current;
	SystemPath m_selected;

	vector3f m_pos;
	vector3f m_posMovingTo;

	float m_rotXDefault, m_rotZDefault, m_zoomDefault;

	float m_rotX, m_rotZ;
	float m_rotXMovingTo, m_rotZMovingTo;

	float m_zoom;
	float m_zoomClamped;
	float m_zoomMovingTo;

	SystemPath m_hyperspaceTarget;
	bool m_matchTargetToSelection;

	bool m_selectionFollowsMovement;

	Gui::Label *m_sectorLabel;
	Gui::Label *m_distanceLabel;
	Gui::Label *m_zoomLevelLabel;
	Gui::ImageButton *m_zoomInButton;
	Gui::ImageButton *m_zoomOutButton;
	Gui::ImageButton *m_galaxyButton;
	Gui::TextEntry *m_searchBox;
	Gui::ToggleButton *m_drawOutRangeLabelButton;
<<<<<<< HEAD
	Gui::ToggleButton *m_drawSystemLegButton;

	ScopedPtr<Graphics::Drawables::Disk> m_disk;
=======
	Gui::ToggleButton *m_drawUninhabitedLabelButton;
	Gui::ToggleButton *m_drawSystemLegButton;

	std::unique_ptr<Graphics::Drawables::Disk> m_disk;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	Gui::LabelSet *m_clickableLabels;

	Gui::VBox *m_infoBox;

	SystemLabels m_currentSystemLabels;
	SystemLabels m_selectedSystemLabels;
	SystemLabels m_targetSystemLabels;
<<<<<<< HEAD
=======
	DistanceIndicator m_secondDistance;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	Gui::Label *m_hyperspaceLockLabel;

	Gui::VBox *m_factionBox;
	std::set<Faction*>              m_visibleFactions;
	std::set<Faction*>              m_hiddenFactions;
	std::vector<Gui::Label*>        m_visibleFactionLabels;
	std::vector<Gui::HBox*>         m_visibleFactionRows;
	std::vector<Gui::ToggleButton*> m_visibleFactionToggles;

	Uint8 m_detailBoxVisible;

	void OnToggleFaction(Gui::ToggleButton* button, bool pressed, Faction* faction);

<<<<<<< HEAD
	sigc::connection m_onMouseButtonDown;
	sigc::connection m_onKeyPressConnection;

	std::map<SystemPath,Sector*> m_sectorCache;
	std::string m_previousSearch;

	float m_playerHyperspaceRange;
=======
	sigc::connection m_onMouseWheelCon;
	sigc::connection m_onKeyPressConnection;

	std::string m_previousSearch;

	float m_playerHyperspaceRange;
	Graphics::Drawables::Line3D m_selectedLine;
	Graphics::Drawables::Line3D m_secondLine;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	Graphics::Drawables::Line3D m_jumpLine;

	RefCountedPtr<Graphics::Material> m_material;

	std::vector<vector3f> m_farstars;
	std::vector<Color>    m_farstarsColor;

	vector3f m_secPosFar;
	int      m_radiusFar;
	bool     m_toggledFaction;

<<<<<<< HEAD
	int m_cacheXMin;
	int m_cacheXMax;
	int m_cacheYMin;
	int m_cacheYMax;
	int m_cacheZMin;
	int m_cacheZMax;

	ScopedPtr<Graphics::VertexArray> m_lineVerts;
=======
	std::unique_ptr<Graphics::VertexArray> m_lineVerts;
	std::unique_ptr<Graphics::VertexArray> m_secLineVerts;
	std::unique_ptr<Graphics::Drawables::Sphere3D> m_jumpSphere;
	std::unique_ptr<Graphics::Drawables::Disk> m_jumpDisk;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
};

#endif /* _SECTORVIEW_H */
