cmake_minimum_required(VERSION 2.8)

macro(LIST_APPEND_PATH VARIABLE EXTRA_PATH)
string(REPLACE ":" ";" LX_EXTRA_PATH ${EXTRA_PATH})
list(APPEND ${VARIABLE} ${LX_EXTRA_PATH})
unset(LX_EXTRA_PATH)
endmacro()

macro(LIST_PREPEND_PATH VARIABLE EXTRA_PATH)
string(REPLACE ":" ";" LX_EXTRA_PATH ${EXTRA_PATH})
list(INSERT ${VARIABLE} 0 ${LX_EXTRA_PATH})
unset(LX_EXTRA_PATH)
endmacro()

# help CMake find C/C++ includes and libraries
LIST_PREPEND_PATH(CMAKE_INCLUDE_PATH $ENV{CPATH})
LIST_PREPEND_PATH(CMAKE_LIBRARY_PATH $ENV{LIBRARY_PATH})
