cmake_minimum_required (VERSION 2.6)
project(JackTest04)

#set(CMAKE_MODULES_PATH ${CMAKE_MODULE_PATH} "${CMAKE_MODULE_PATH}/cmake/Modules/")

# find lib
find_library(JACK_LIBRARY jack)
set(LIBS ${LIBS} ${JACK_LIBRARY})

find_library(SNDFILE_LIBRARY NAMES libsndfile-1 PATHS "C:/Programming/libsndfile" PATH_SUFFXES "lib" "bin")
set(LIBS ${LIBS} ${SNDFILE_LIBRARY})

# find inc
find_path(JACK_INCLUDE_DIR
	NAMES jack/jack.h
	PATHS "C:/Program Files (x86)/Jack"
	PATH_SUFFIXES "include" "includes"
)

find_path(SNDFILE_INCLUDE_DIR
	NAMES sndfile.h
	PATHS "C:/Programming/libsndfile"
	PATH_SUFFIXES "include" "includes"
)

set(INCLUDES ${JACK_INCLUDE_DIR} ${SNDFILE_INCLUDE_DIR})

# create exec
file(GLOB inFiles *.cpp *.h)
add_executable(JackTest04 ${inFiles})
target_link_libraries(JackTest04 ${LIBS})
include_directories(${INCLUDES})
