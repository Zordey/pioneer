#  Process this file with automake to produce Makefile.in

include $(top_srcdir)/Makefile.common

AM_CFLAGS += $(WARN_CFLAGS)
AM_CPPFLAGS += $(WARN_CPPFLAGS)
<<<<<<< HEAD
AM_CXXFLAGS += $(WARN_CXXFLAGS)
INCLUDES = -isystem $(top_srcdir)/contrib
=======
AM_CXXFLAGS += $(STD_CXXFLAGS) $(WARN_CXXFLAGS)

INCLUDES = -I$(srcdir)/.. -isystem $(top_srcdir)/contrib
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

noinst_LIBRARIES = libcollider.a
libcollider_a_SOURCES = \
	BVHTree.cpp \
	CollisionSpace.cpp \
	Geom.cpp \
	GeomTree.cpp

noinst_HEADERS = \
	BVHTree.h \
	CollisionContact.h \
	CollisionSpace.h \
	Geom.h \
	GeomTree.h \
	collider.h
