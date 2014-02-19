include $(top_srcdir)/Makefile.common

AM_CFLAGS += $(WARN_CFLAGS)
AM_CPPFLAGS += $(WARN_CPPFLAGS) -DPIONEER_DATA_DIR=\"@PIONEER_DATA_DIR@\"
<<<<<<< HEAD
AM_CXXFLAGS += $(WARN_CXXFLAGS)
=======
AM_CXXFLAGS += $(STD_CXXFLAGS) $(WARN_CXXFLAGS)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

AM_CPPFLAGS += -I$(top_srcdir)/src -isystem $(top_srcdir)/contrib

noinst_LIBRARIES = libposix.a
libposix_a_SOURCES = \
	FileSystemPosix.cpp \
	OSPosix.cpp
