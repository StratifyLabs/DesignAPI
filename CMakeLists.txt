cmake_minimum_required (VERSION 3.12)

project(LibraryAPI CXX)
include(CTest)

add_subdirectory(library library)

option(LIBRRAY_API_IS_TEST "Enable test builds for LibraryAPI" OFF)
if(LIBRRAY_API_IS_TEST)
	add_subdirectory(tests tests)
endif()

