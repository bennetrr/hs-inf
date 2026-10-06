cmake_minimum_required(VERSION 3.10)
project(CGCLib)

# Collect source files
file(GLOB_RECURSE LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
add_library(cgclib ${LIB_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Files" FILES ${LIB_SOURCES})

# Platform-specific dependencies
if(UNIX AND NOT APPLE)

    # On Linux, make sure these are installed:
    # sudo apt install libx11-dev libgl1-mesa-dev

    if(POLICY CMP0072)
        cmake_policy(SET CMP0072 NEW)
    endif()
    set(OpenGL_GL_PREFERENCE GLVND)
    
    find_package(X11 REQUIRED)
    find_package(OpenGL REQUIRED)

    target_include_directories(cgclib PUBLIC ${X11_INCLUDE_DIR})

    if(TARGET OpenGL::GL)
        target_link_libraries(cgclib PUBLIC ${X11_LIBRARIES} OpenGL::GL m)
    else()
        target_link_libraries(cgclib PUBLIC ${X11_LIBRARIES} ${OPENGL_LIBRARIES} m)
    endif()



endif()

if(APPLE)
    # tigr uses Cocoa (via the Objective-C runtime) and OpenGL on macOS
    target_link_libraries(cgclib PUBLIC "-framework Cocoa" "-framework OpenGL")
endif()

# Project includes
target_include_directories(cgclib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Optional: organize in IDEs
set_target_properties(cgclib PROPERTIES FOLDER "cgclib")