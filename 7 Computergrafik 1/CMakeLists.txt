cmake_minimum_required(VERSION 3.10)
project(cgclab C)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_C_STANDARD 23)
find_package(OpenMP REQUIRED)
set(CGCLIB_C_FLAGS_FLAGS "/O2 /GL /Ot /arch:AVX2 /fp:fast /Ob2 /Ot /fp:except- /Oi /MP /GS- /sdl- /Zi")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${CGCLIB_C_FLAGS_FLAGS}")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${CGCLIB_C_FLAGS_FLAGS}")

add_subdirectory(cgclib)
add_subdirectory(labs)
add_subdirectory(contrib)
add_subdirectory(tests)
add_subdirectory(learnc)