<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Table.h"
#include "Context.h"
#include "Slider.h"

namespace UI {

void Table::LayoutAccumulator::AddRow(const std::vector<Widget*> &widgets)
{
<<<<<<< HEAD
	if (m_columnWidths.size() < widgets.size()) {
		std::size_t i = m_columnWidths.size();
		m_columnWidths.resize(widgets.size());
		for (; i < widgets.size(); i++)
			m_columnWidths[i] = 0;
	}

	int height = 0;
=======
	if (m_columnWidth.size() < widgets.size()) {
		std::size_t i = m_columnWidth.size();
		m_columnWidth.resize(widgets.size());
		m_columnLeft.resize(widgets.size());
		for (; i < widgets.size(); i++)
			m_columnWidth[i] = m_columnLeft[i] = 0;
	}

	m_columnLeft[0] = 0;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	for (std::size_t i = 0; i < widgets.size(); i++) {
		Widget *w = widgets[i];
		if (!w) continue;
		const Point size(w->CalcLayoutContribution());
		// XXX handle flags
<<<<<<< HEAD
		m_columnWidths[i] = std::max(m_columnWidths[i], size.x);
		height = std::max(height, size.y);
	}
	m_size.y += height;

	m_size.x = 0;
	for (std::size_t i = 0; i < m_columnWidths.size(); i++)
		m_size.x += m_columnWidths[i];
=======
		m_columnWidth[i] = std::max(m_columnWidth[i], size.x);
		if (i > 0) m_columnLeft[i] = m_columnLeft[i-1] + m_columnWidth[i-1] + m_columnSpacing;
	}
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Table::LayoutAccumulator::Clear()
{
<<<<<<< HEAD
	m_columnWidths.clear();
	m_size = Point();
=======
	m_columnWidth.clear();
	m_columnLeft.clear();
}

void Table::LayoutAccumulator::SetColumnSpacing(int spacing) {
	m_columnSpacing = spacing;
	m_columnLeft.resize(m_columnWidth.size());
	if (m_columnLeft.size() > 0) {
		m_columnLeft[0] = 0;
		for (std::size_t i = 0; i < m_columnWidth.size(); i++)
			if (i > 0) m_columnLeft[i] = m_columnLeft[i-1] + m_columnWidth[i-1] + m_columnSpacing;
	}
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

Table::Inner::Inner(Context *context, LayoutAccumulator &layout) : Container(context),
	m_layout(layout),
	m_rowSpacing(0),
<<<<<<< HEAD
	m_columnSpacing(0),
	m_dirty(false)
=======
	m_rowAlignment(TOP),
	m_dirty(false),
	m_mouseEnabled(false)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{
}

Point Table::Inner::PreferredSize()
{
<<<<<<< HEAD
	m_preferredSizes.clear();
	m_preferredSize = Point();

	for (std::size_t i = 0; i < m_rows.size(); i++) {
		const std::vector<Widget*> &row = m_rows[i];
		Point rowSize;
		std::vector<Point> preferredSizes(row.size());
=======
	if (!m_dirty)
		return m_preferredSize;

	const std::vector<int> &colWidth = m_layout.ColumnWidth();
	const std::vector<int> &colLeft = m_layout.ColumnLeft();
	if (colWidth.size() == 0) {
		m_preferredSize = Point();
		return m_preferredSize;
	}

	m_preferredSize.x = colLeft.back() + colWidth.back();
	m_preferredSize.y = 0;

	m_rowHeight.resize(m_rows.size());

	for (std::size_t i = 0; i < m_rows.size(); i++) {
		const std::vector<Widget*> &row = m_rows[i];
		m_rowHeight[i] = 0;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		for (std::size_t j = 0; j < row.size(); j++) {
			Widget *w = row[j];
			if (!w) continue;
			Point size(w->CalcLayoutContribution());
<<<<<<< HEAD
			preferredSizes[j] = size;
			rowSize.x += size.x;
			rowSize.y = std::max(rowSize.y, size.y);
		}
		m_preferredSizes.push_back(preferredSizes);

		if (!row.empty() && m_columnSpacing)
			m_preferredSize.x += (row.size()-1)*m_columnSpacing;

		m_preferredSize.x = std::max(m_preferredSize.x, rowSize.x);
		m_preferredSize.y += rowSize.y;
=======
			m_rowHeight[i] = std::max(m_rowHeight[i], size.y);
		}
		m_preferredSize.y += m_rowHeight[i];
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	}

	if (!m_rows.empty() && m_rowSpacing)
		m_preferredSize.y += (m_rows.size()-1)*m_rowSpacing;

	m_dirty = false;
<<<<<<< HEAD

=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return m_preferredSize;
}

void Table::Inner::Layout()
{
	if (m_dirty)
		PreferredSize();

<<<<<<< HEAD
	Point pos;
	const std::vector<int> &colWidths = m_layout.ColumnWidths();

	for (std::size_t i = 0; i < m_rows.size(); i++) {
		const std::vector<Widget*> &row = m_rows[i];
		const std::vector<Point> &preferredSizes = m_preferredSizes[i];
		pos.x = 0;
		int height = 0;
		for (std::size_t j = 0; j < row.size(); j++) {
			Widget *w = row[j];
			const Point &preferredSize = preferredSizes[j];
			if (!w) continue;
			SetWidgetDimensions(w, pos, preferredSize);
			pos.x += colWidths[j] + m_columnSpacing;
			height = std::max(height, preferredSize.y);
		}
		pos.y += height + m_rowSpacing;
=======
	int rowTop = 0;

	const std::vector<int> &colWidth = m_layout.ColumnWidth();
	const std::vector<int> &colLeft = m_layout.ColumnLeft();

	for (std::size_t i = 0; i < m_rows.size(); i++) {
		const std::vector<Widget*> &row = m_rows[i];
		for (std::size_t j = 0; j < row.size(); j++) {
			Widget *w = row[j];
			if (!w) continue;

			const Point preferredSize(w->PreferredSize());
			int height = std::min(preferredSize.y, m_rowHeight[i]);

			int off = 0;
			if (height != m_rowHeight[i]) {
				switch (m_rowAlignment) {
					case CENTER:
						off = (m_rowHeight[i] - height) / 2;
						break;
					case BOTTOM:
						off = m_rowHeight[i] - height;
						break;
					default:
						off = 0;
						break;
				}
			}

			SetWidgetDimensions(w, Point(colLeft[j], rowTop+off), Point(colWidth[j], height));
		}

		rowTop += m_rowHeight[i] + m_rowSpacing;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	}

	LayoutChildren();
}

<<<<<<< HEAD
=======
void Table::Inner::Draw()
{
	int row_top, row_bottom;
	if (m_mouseEnabled && IsMouseOver() && RowUnderPoint(GetMousePos(), &row_top, &row_bottom) >= 0) {
		GetContext()->GetSkin().DrawRectHover(Point(0, row_top), Point(GetSize().x, row_bottom - row_top));
	}

	Container::Draw();
}

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
void Table::Inner::AddRow(const std::vector<Widget*> &widgets)
{
	m_rows.push_back(widgets);

	Point rowSize;
	for (std::size_t i = 0; i < widgets.size(); i++) {
		if (!widgets[i]) continue;
		AddWidget(widgets[i]);
	}

	m_dirty = true;
}

void Table::Inner::Clear()
{
	for (std::vector< std::vector<Widget*> >::const_iterator i = m_rows.begin(); i != m_rows.end(); ++i) {
		for (std::size_t j = 0; j < (*i).size(); j++) {
			if (!(*i)[j]) continue;
			RemoveWidget((*i)[j]);
		}
	}

	m_rows.clear();
	m_preferredSize = Point();
<<<<<<< HEAD
=======

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	m_dirty = false;
}

void Table::Inner::AccumulateLayout()
{
	for (std::vector< std::vector<Widget*> >::const_iterator i = m_rows.begin(); i != m_rows.end(); ++i)
		m_layout.AddRow(*i);
<<<<<<< HEAD
=======

	m_dirty = true;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Table::Inner::SetRowSpacing(int spacing)
{
	m_rowSpacing = spacing;
	m_dirty = true;
}

<<<<<<< HEAD
void Table::Inner::SetColumnSpacing(int spacing)
{
	m_columnSpacing = spacing;
	m_dirty = true;
}

void Table::Inner::SetSpacing(int spacing)
{
	m_rowSpacing = m_columnSpacing = spacing;
	m_dirty = true;
}

=======
void Table::Inner::SetRowAlignment(RowAlignDirection dir)
{
	m_rowAlignment = dir;
	m_dirty = true;
}

void Table::Inner::HandleClick()
{
	if (m_mouseEnabled) {
		int row = RowUnderPoint(GetMousePos());
		if (row >= 0)
			onRowClicked.emit(row);
	}

	Container::HandleClick();
}

int Table::Inner::RowUnderPoint(const Point &pt, int *out_row_top, int *out_row_bottom) const
{
	int start = 0, end = m_rows.size()-1, mid = 0;
	while (start <= end) {
		mid = start+((end-start)/2);

		const Widget *w = m_rows[mid][0];
		const int rowTop = w->GetPosition().y;
		const int rowBottom = rowTop + w->GetSize().y;

		if (pt.y < rowTop)
			end = mid-1;
		else if (pt.y >= rowBottom)
			start = mid+1;
		else {
			if (out_row_top) { *out_row_top = rowTop; }
			if (out_row_bottom) { *out_row_bottom = rowBottom; }
			return mid;
		}
	}

	if (out_row_top) { *out_row_top = 0; }
	if (out_row_bottom) { *out_row_bottom = 0; }
	return -1;
}


>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
Table::Table(Context *context) : Container(context),
	m_dirty(false)
{
	m_header.Reset(new Table::Inner(GetContext(), m_layout));
	AddWidget(m_header.Get());

	m_body.Reset(new Table::Inner(GetContext(), m_layout));
	AddWidget(m_body.Get());

<<<<<<< HEAD
=======
	m_body->onRowClicked.connect(sigc::mem_fun(&onRowClicked, &sigc::signal<void,unsigned int>::emit));

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	m_slider.Reset(GetContext()->VSlider());
	m_slider->onValueChanged.connect(sigc::mem_fun(this, &Table::OnScroll));
}

Point Table::PreferredSize()
{
<<<<<<< HEAD
	m_layout.Clear();

	m_header->AccumulateLayout();
	m_body->AccumulateLayout();

	m_dirty = false;

	const Point layoutSize = m_layout.GetSize();
=======
	if (m_dirty) {
		m_layout.Clear();

		m_header->AccumulateLayout();
		m_body->AccumulateLayout();

		m_dirty = false;
	}

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	const Point sliderSize = m_slider->PreferredSize();

	const Point headerPreferredSize = m_header->PreferredSize();
	const Point bodyPreferredSize = m_body->PreferredSize();

<<<<<<< HEAD
	return Point(layoutSize.x+sliderSize.x, headerPreferredSize.y+bodyPreferredSize.y);
=======
	return Point(std::max(headerPreferredSize.x,bodyPreferredSize.x)+sliderSize.x, headerPreferredSize.y+bodyPreferredSize.y);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Table::Layout()
{
	if (m_dirty)
		PreferredSize();

	Point size = GetSize();

	Point preferredSize(m_header->PreferredSize());
	SetWidgetDimensions(m_header.Get(), Point(), Point(size.x, preferredSize.y));
	int top = preferredSize.y;
	size.y -= top;

<<<<<<< HEAD
	Point sliderSize;

	preferredSize = m_body->PreferredSize();
	if (preferredSize.y <= size.y) {
		if (m_slider->GetContainer()) {
=======
	preferredSize = m_body->PreferredSize();
	if (preferredSize.y <= size.y) {
		if (m_slider->GetContainer()) {
			m_slider->SetValue(0);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			m_onMouseWheelConn.disconnect();
			RemoveWidget(m_slider.Get());
		}
	}
	else {
		AddWidget(m_slider.Get());
<<<<<<< HEAD
		m_onMouseWheelConn = onMouseWheel.connect(sigc::mem_fun(this, &Table::OnMouseWheel));
		sliderSize = m_slider->PreferredSize();
		SetWidgetDimensions(m_slider.Get(), Point(size.x-sliderSize.x, top), Point(sliderSize.x, size.y));
		size.x -= sliderSize.x;
=======
		if (!m_onMouseWheelConn.connected())
			m_onMouseWheelConn = onMouseWheel.connect(sigc::mem_fun(this, &Table::OnMouseWheel));

		const Point sliderSize(m_slider->PreferredSize().x, size.y);
		const Point sliderPos(size.x-sliderSize.x, top);
		SetWidgetDimensions(m_slider.Get(), sliderPos, sliderSize);

		size.x = sliderPos.x;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	}

	SetWidgetDimensions(m_body.Get(), Point(0, top), size);

	LayoutChildren();
}

<<<<<<< HEAD
=======
void Table::HandleInvisible()
{
	m_slider->SetValue(0);
}

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
Table *Table::SetHeadingRow(const WidgetSet &set)
{
	m_header->Clear();
	m_header->AddRow(set.widgets);
<<<<<<< HEAD

	m_dirty = true;
=======
	m_dirty = true;
	GetContext()->RequestLayout();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return this;
}

Table *Table::AddRow(const WidgetSet &set)
{
	m_body->AddRow(set.widgets);
<<<<<<< HEAD

	m_dirty = true;

	return this;

=======
	m_dirty = true;
	GetContext()->RequestLayout();
	return this;
}

void Table::ClearRows()
{
	m_body->Clear();
	m_dirty = true;
	GetContext()->RequestLayout();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

Table *Table::SetRowSpacing(int spacing)
{
<<<<<<< HEAD
	m_header->SetRowSpacing(spacing);
	m_body->SetRowSpacing(spacing);
	m_dirty = true;
=======
	m_body->SetRowSpacing(spacing);
	m_dirty = true;
	GetContext()->RequestLayout();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return this;
}

Table *Table::SetColumnSpacing(int spacing)
{
<<<<<<< HEAD
	m_header->SetColumnSpacing(spacing);
	m_body->SetColumnSpacing(spacing);
	m_dirty = true;
	return this;
}

Table *Table::SetSpacing(int spacing)
{
	m_header->SetSpacing(spacing);
	m_body->SetSpacing(spacing);
	m_dirty = true;
=======
	m_layout.SetColumnSpacing(spacing);
	m_dirty = true;
	GetContext()->RequestLayout();
	return this;
}

Table *Table::SetRowAlignment(RowAlignDirection dir)
{
	m_body->SetRowAlignment(dir);
	m_dirty = true;
	GetContext()->RequestLayout();
	return this;
}

Table *Table::SetHeadingFont(Font font)
{
	m_header->SetFont(font);
	m_dirty = true;
	GetContext()->RequestLayout();
	return this;
}

Table *Table::SetMouseEnabled(bool enabled)
{
	m_body->SetMouseEnabled(enabled);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return this;
}


void Table::OnScroll(float value)
{
	m_body->SetDrawOffset(Point(0, -float(m_body->PreferredSize().y-(GetSize().y-m_header->PreferredSize().y))*value));
}

bool Table::OnMouseWheel(const MouseWheelEvent &event)
{
	m_slider->SetValue(m_slider->GetValue() + (event.direction == MouseWheelEvent::WHEEL_UP ? -0.01f : 0.01f));
	return true;
}


}
