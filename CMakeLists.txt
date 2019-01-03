

cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)

project(l298n-driver)

set (CMAKE_CXX_STANDARD 11)

add_definitions(-std=c++11 -lpigpiod_if2 -lrt)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#find_package( Ceres REQUIRED )


include_directories(
	${PROJECT_SOURCE_DIR}/inc
)

#add_library(
#	OrientedPoint STATIC
#	${PROJECT_SOURCE_DIR}/src/OrientedPoint.cpp
#	${PROJECT_SOURCE_DIR}/src/View.cpp
#	${PROJECT_SOURCE_DIR}/src/Track.cpp
#)

#include_directories(
#	${PROJECT_SOURCE_DIR}/inc
#	${CERES_INCLUDE_DIRS}
#)

#target_link_libraries( Match
#	${OpenCV_LIBS}
#	OrientedPoint
#)

add_library( l298n-driver STATIC
	${PROJECT_SOURCE_DIR}/src/l298n.cpp
)
target_link_libraries( l298n-driver
	pigpiod_if2
	rt
)
target_include_directories ( l298n-driver
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_executable( test1
	${PROJECT_SOURCE_DIR}/test/test.cpp
)
target_link_libraries( test1
	l298n-driver
	-pthread
)
