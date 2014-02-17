include $(top_srcdir)/Makefile.common

AM_CFLAGS += $(WARN_CFLAGS)
AM_CPPFLAGS += $(WARN_CPPFLAGS)
<<<<<<< HEAD
AM_CXXFLAGS += $(WARN_CXXFLAGS)
=======
AM_CXXFLAGS += $(STD_CXXFLAGS) $(WARN_CXXFLAGS)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

INCLUDES = -isystem $(top_srcdir)/contrib -I$(srcdir)/..
if !HAVE_LUA
INCLUDES += -isystem $(top_srcdir)/contrib/lua
endif

noinst_LIBRARIES = libgameui.a
noinst_HEADERS = \
	GameUI.h \
	Lua.h \
	Panel.h \
	Face.h \
<<<<<<< HEAD
	ModelSpinner.h
=======
	ModelSpinner.h \
	BindingCapture.h
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

libgameui_a_SOURCES = \
	Panel.cpp \
	Face.cpp \
	ModelSpinner.cpp \
<<<<<<< HEAD
	Lua.cpp \
	LuaFace.cpp \
	LuaModelSpinner.cpp
=======
	BindingCapture.cpp \
	Lua.cpp \
	LuaFace.cpp \
	LuaModelSpinner.cpp \
	LuaBindingCapture.cpp
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
