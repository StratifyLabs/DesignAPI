cmake_minimum_required (VERSION 3.12)
cmsdk2_minimum_required(2.1.2)
project(DesignAPI
	LANGUAGES CXX
	VERSION 1.0.1)
include(CTest)
add_subdirectory(library library)
option(DESIGN_API_IS_TEST "Enable test builds for DesignAPI" OFF)
if(DESIGN_API_IS_TEST)
	add_subdirectory(tests tests)
endif()

