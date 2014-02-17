include $(top_srcdir)/Makefile.common

AM_CFLAGS += $(WARN_CFLAGS)
AM_CPPFLAGS += $(WARN_CPPFLAGS)
<<<<<<< HEAD
AM_CXXFLAGS += $(WARN_CXXFLAGS)
=======
AM_CXXFLAGS += $(STD_CXXFLAGS) $(WARN_CXXFLAGS)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

INCLUDES = -I$(srcdir)/.. -isystem $(top_srcdir)/contrib

noinst_LIBRARIES = libtext.a
noinst_HEADERS = \
	DistanceFieldFont.h \
	FontDescriptor.h \
	Font.h \
	TextSupport.h \
	TextureFont.h

libtext_a_SOURCES = \
	DistanceFieldFont.cpp \
	FontDescriptor.cpp \
	Font.cpp \
	TextSupport.cpp \
	TextureFont.cpp
