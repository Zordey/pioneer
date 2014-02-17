<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_TABLE_H
#define UI_TABLE_H

#include "Container.h"
#include "Slider.h"
<<<<<<< HEAD
=======
#include "Event.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

namespace UI {

class Table: public Container {
protected:
	friend class Context;
	Table(Context *context);

public:
	virtual Point PreferredSize();
	virtual void Layout();

	Table *SetHeadingRow(const WidgetSet &set);
	Table *AddRow(const WidgetSet &set);
<<<<<<< HEAD

	Table *SetRowSpacing(int spacing);
	Table *SetColumnSpacing(int spacing);
	Table *SetSpacing(int spacing);
=======
	void ClearRows();

	Table *SetRowSpacing(int spacing);
	Table *SetColumnSpacing(int spacing);

	enum RowAlignDirection { // <enum scope='UI::Table' name=UITableRowAlignDirection public>
		TOP,
		CENTER,
		BOTTOM
	};

	Table *SetRowAlignment(RowAlignDirection dir);

	Table *SetHeadingFont(Font font);

	Table *SetMouseEnabled(bool enabled);

	sigc::signal<void,unsigned int> onRowClicked;

protected:
	virtual void HandleInvisible();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

private:

	class LayoutAccumulator {
	public:
<<<<<<< HEAD
		void AddRow(const std::vector<Widget*> &widgets);
		void Clear();

		void SetSpacing(int h, int v);

		const std::vector<int> &ColumnWidths() const { return m_columnWidths; }
		const Point &GetSize() const { return m_size; }
	private:
		std::vector<int> m_columnWidths;
		Point m_size;
=======
		LayoutAccumulator() : m_columnSpacing(0) {}

		void AddRow(const std::vector<Widget*> &widgets);
		void Clear();

		void SetColumnSpacing(int spacing);

		const std::vector<int> &ColumnWidth() const { return m_columnWidth; }
		const std::vector<int> &ColumnLeft() const { return m_columnLeft; }

	private:
		std::vector<int> m_columnWidth;

		void UpdateColumns();
		std::vector<int> m_columnLeft;
		int m_columnSpacing;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	};


	class Inner: public Container {
	public:
		Inner(Context *context, LayoutAccumulator &layout);

		virtual Point PreferredSize();
		virtual void Layout();
<<<<<<< HEAD
=======
		virtual void Draw();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

		void AddRow(const std::vector<Widget*> &widgets);
		void Clear();

		void AccumulateLayout();

		void SetRowSpacing(int spacing);
		void SetColumnSpacing(int spacing);
<<<<<<< HEAD
		void SetSpacing(int spacing);

	private:
		LayoutAccumulator &m_layout;
		std::vector< std::vector<Widget*> > m_rows;
		std::vector< std::vector<Point> > m_preferredSizes;
		Point m_preferredSize;
		int m_rowSpacing;
		int m_columnSpacing;
		bool m_dirty;
=======

		void SetRowAlignment(RowAlignDirection dir);

		void SetMouseEnabled(bool enabled) { m_mouseEnabled = enabled; }

		sigc::signal<void,unsigned int> onRowClicked;

	protected:
		virtual void HandleClick();

	private:
		int RowUnderPoint(const Point &pt, int *out_row_top = 0, int *out_row_bottom = 0) const;

		LayoutAccumulator &m_layout;
		std::vector< std::vector<Widget*> > m_rows;
		std::vector<int> m_rowHeight;
		Point m_preferredSize;
		int m_rowSpacing;
		RowAlignDirection m_rowAlignment;
		bool m_dirty;

		bool m_mouseEnabled;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	};

	LayoutAccumulator m_layout;
	bool m_dirty;

	RefCountedPtr<Inner> m_header;
	RefCountedPtr<Inner> m_body;

	RefCountedPtr<Slider> m_slider;

	sigc::connection m_onMouseWheelConn;

	void OnScroll(float value);
	bool OnMouseWheel(const MouseWheelEvent &event);
};

}

#endif

