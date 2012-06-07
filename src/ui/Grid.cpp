#include "Grid.h"

namespace UI {

Grid::Grid(Context *context, const CellSpec &rowSpec, const CellSpec &colSpec) : Container(context),
	m_rowSpec(rowSpec),
	m_colSpec(colSpec),
	m_numRows(colSpec.numCells),
	m_numCols(rowSpec.numCells),
	m_widgets(m_rowSpec.numCells*m_colSpec.numCells)
{
	Clear();
}

void Grid::Layout()
{
	const vector2f size = GetSize();

	vector2f childPos, childSize;
	for (int rowNum = 0; rowNum < m_numRows; rowNum++) {
		childSize.y = m_colSpec.cellPercent[rowNum]*size.y;

		childPos.x = 0;
		for (int colNum = 0; colNum < m_numCols; colNum++) {
			childSize.x = m_rowSpec.cellPercent[colNum]*size.x;

			const int n = rowNum*m_numCols+colNum;
			if (m_widgets[n])
				SetWidgetDimensions(m_widgets[n], childPos, childSize);

			childPos.x += childSize.x;
		}

		childPos.y += childSize.y;
	}

	LayoutChildren();
}

Grid *Grid::SetRow(int rowNum, const WidgetSet &set)
{
	assert(set.numWidgets <= m_rowSpec.numCells);
	assert(rowNum >= 0 && rowNum < m_numRows);

	for (int i = 0; i < set.numWidgets; i++) {
		const int n = rowNum*m_numCols+i;
		if (m_widgets[n])
			RemoveWidget(m_widgets[n]);
		m_widgets[n] = set.widgets[i];
		AddWidget(m_widgets[n]);
	}

	return this;
}

Grid *Grid::SetColumn(int colNum, const WidgetSet &set)
{
	assert(set.numWidgets <= m_colSpec.numCells);
	assert(colNum >= 0 && colNum < m_numCols);

	for (int i = 0; i < set.numWidgets; i++) {
		const int n = i*m_numCols+colNum;
		if (m_widgets[n])
			RemoveWidget(m_widgets[n]);
		m_widgets[n] = set.widgets[i];
		AddWidget(m_widgets[n]);
	}

	return this;
}

Grid *Grid::SetCell(int colNum, int rowNum, Widget *widget)
{
	assert(colNum > 0 && colNum < m_numCols);
	assert(rowNum > 0 && rowNum < m_numRows);

	const int n = rowNum*m_numCols+colNum;
	if (m_widgets[n])
		RemoveWidget(m_widgets[n]);
	m_widgets[n] = widget;
	AddWidget(m_widgets[n]);

	return this;
}

void Grid::ClearRow(int rowNum)
{
	assert(rowNum >= 0 && rowNum < m_numRows);

	for (int i = 0; i < m_numCols; i++) {
		const int n = rowNum*m_numCols+i;
		if (m_widgets[n]) {
			RemoveWidget(m_widgets[n]);
			m_widgets[n] = 0;
		}
	}
}

void Grid::ClearColumn(int colNum)
{
	assert(colNum >= 0 && colNum < m_numRows);

	for (int i = 0; i < m_numRows; i++) {
		const int n = i*m_numCols+colNum;
		if (m_widgets[n]) {
			RemoveWidget(m_widgets[n]);
			m_widgets[n] = 0;
		}
	}
}

void Grid::Clear()
{
	for (int i = 0; i < m_numRows*m_numCols; i++)
		m_widgets[i] = 0;

	RemoveAllWidgets();
}

}
