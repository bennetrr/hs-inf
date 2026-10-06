cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 23)
add_library(unity
	src/unity.c
	include/unity/unity.h
	include/unity/unity_internals.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/unity)
target_include_directories(unity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(unity PROPERTIES FOLDER "Contrib")