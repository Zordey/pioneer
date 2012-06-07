#ifndef _UI_GRID_H
#define _UI_GRID_H

#include "Container.h"
#include "CellSpec.h"

namespace UI {

class Grid : public Container {
protected:
	friend class Context;
	Grid(Context *context, const CellSpec &rowSpec, const CellSpec &colSpec);

public:
	virtual void Layout();

	Grid *SetRow(int rowNum, const WidgetSet &set);
	Grid *SetColumn(int colNum, const WidgetSet &set);
	Grid *SetCell(int colNum, int rowNum, Widget *widget);

	void ClearRow(int rowNum);
	void ClearColumn(int colNum);
	void Clear();

private:
	CellSpec m_rowSpec, m_colSpec;
	std::vector<Widget*> m_widgets;
};

}

#endif
