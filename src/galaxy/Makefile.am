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

noinst_LIBRARIES = libgalaxy.a
noinst_HEADERS = \
	CustomSystem.h \
	Galaxy.h \
	Sector.h \
<<<<<<< HEAD
=======
	SectorCache.h \
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	StarSystem.h \
	SystemPath.h

libgalaxy_a_SOURCES = \
	CustomSystem.cpp \
	Galaxy.cpp \
	Sector.cpp \
<<<<<<< HEAD
=======
	SectorCache.cpp \
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	StarSystem.cpp \
	SystemPath.cpp
