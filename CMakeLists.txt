cmake_minimum_required (VERSION 3.12)
project(DesignAPI CXX)
include(CTest)
add_subdirectory(library library)
option(DESIGN_API_IS_TEST "Enable test builds for DesignAPI" OFF)
if(DESIGN_API_IS_TEST)
	add_subdirectory(tests tests)
endif()

