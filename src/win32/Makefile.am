include $(top_srcdir)/Makefile.common

AM_CFLAGS += $(WARN_CFLAGS)
AM_CPPFLAGS += $(WARN_CPPFLAGS)
<<<<<<< HEAD
AM_CXXFLAGS += $(WARN_CXXFLAGS)
=======
AM_CXXFLAGS += $(STD_CXXFLAGS) $(WARN_CXXFLAGS)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

INCLUDES = -I$(srcdir)/.. -isystem $(top_srcdir)/contrib

noinst_LIBRARIES = libwin32.a
libwin32_a_SOURCES = \
	FileSystemWin32.cpp \
	OSWin32.cpp
