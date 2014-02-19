include $(top_srcdir)/Makefile.common

AM_CFLAGS += $(WARN_CFLAGS)
AM_CPPFLAGS += $(WARN_CPPFLAGS)
<<<<<<< HEAD
AM_CXXFLAGS += $(WARN_CXXFLAGS)
=======
AM_CXXFLAGS += $(STD_CXXFLAGS) $(WARN_CXXFLAGS)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

AM_CPPFLAGS += -isystem $(top_srcdir)/contrib -I$(srcdir)/..
if !HAVE_LUA
AM_CPPFLAGS += -isystem $(top_srcdir)/contrib/lua
endif

noinst_LIBRARIES = libui.a
noinst_HEADERS = \
	Align.h \
	Background.h \
	Box.h \
	Button.h \
	CellSpec.h \
	CheckBox.h \
	ColorBackground.h \
	Container.h \
	Context.h \
	DropDown.h \
	Event.h \
	EventDispatcher.h \
	Expand.h \
<<<<<<< HEAD
	FloatContainer.h \
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	Gauge.h \
	Gradient.h \
	Grid.h \
	Icon.h \
	Image.h \
	Label.h \
<<<<<<< HEAD
=======
	Layer.h \
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	List.h \
	Lua.h \
	LuaSignal.h \
	Margin.h \
	MultiLineText.h \
	NumberLabel.h \
	Point.h \
	Scroller.h \
	Single.h \
	Skin.h \
	Slider.h \
	SmallButton.h \
	Table.h \
	TextEntry.h \
	TextLayout.h \
	Widget.h \
	WidgetSet.h

libui_a_SOURCES = \
	Align.cpp \
	Background.cpp \
	Box.cpp \
	Button.cpp \
	CellSpec.cpp \
	CheckBox.cpp \
	ColorBackground.cpp \
	Container.cpp \
	Context.cpp \
	DropDown.cpp \
	Event.cpp \
	EventDispatcher.cpp \
	Expand.cpp \
<<<<<<< HEAD
	FloatContainer.cpp \
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	Gauge.cpp \
	Gradient.cpp \
	Grid.cpp \
	Icon.cpp \
	Image.cpp \
	Label.cpp \
<<<<<<< HEAD
=======
	Layer.cpp \
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	List.cpp \
	Margin.cpp \
	MultiLineText.cpp \
	NumberLabel.cpp \
	Scroller.cpp \
	Single.cpp \
	Skin.cpp \
	Slider.cpp \
	SmallButton.cpp \
	Table.cpp \
	TextEntry.cpp \
	TextLayout.cpp \
	Widget.cpp \
	Lua.cpp \
	LuaAlign.cpp \
	LuaBackground.cpp \
	LuaBox.cpp \
	LuaButton.cpp \
	LuaCheckBox.cpp \
	LuaColorBackground.cpp \
	LuaContainer.cpp \
	LuaContext.cpp \
	LuaDropDown.cpp \
	LuaGradient.cpp \
	LuaExpand.cpp \
	LuaGauge.cpp \
	LuaGrid.cpp \
	LuaIcon.cpp \
	LuaImage.cpp \
	LuaLabel.cpp \
<<<<<<< HEAD
=======
	LuaLayer.cpp \
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	LuaList.cpp \
	LuaMargin.cpp \
	LuaMultiLineText.cpp \
	LuaNumberLabel.cpp \
	LuaScroller.cpp \
	LuaSingle.cpp \
	LuaSlider.cpp \
	LuaSmallButton.cpp \
	LuaTable.cpp \
	LuaTextEntry.cpp \
	LuaWidget.cpp
