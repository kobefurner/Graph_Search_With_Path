# Set minimum CMAKE
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project( GraphChallenge )

# require C++14
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( APP_EXECUTABLE GraphTest )

set( LIB_NAME classLibrary )
add_library( ${LIB_NAME} STATIC inc/GameState.h inc/MC.h )
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set ( LIB_GRAPH graphLibrary )
add_library( ${LIB_GRAPH} INTERFACE inc/Graph.hpp)
target_include_directories( ${LIB_GRAPH} INTERFACE inc )

ADD_EXECUTABLE( ${APP_EXECUTABLE} src/GraphTest.cpp )
TARGET_LINK_LIBRARIES( ${APP_EXECUTABLE} ${LIB_GRAPH} )

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${APP_EXECUTABLE} )

include (CTest)
add_test(${APP_EXECUTABLE}_numbers ${APP_EXECUTABLE} 1)
add_test(${APP_EXECUTABLE}_missionary_cannibals ${APP_EXECUTABLE} 2)


find_program(VALGRIND "valgrind")
if(VALGRIND)
	add_custom_target(valgrind
		COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes --show-reachable=yes --error-exitcode=1 $<TARGET_FILE:${APP_EXECUTABLE}>)
endif()
