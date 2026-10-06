function(CreateTest)

    # Parse optional SOURCES argument
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(CT "" "" "${multiValueArgs}" ${ARGN})

    # Base name of the current directory
    get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

    # Base name of the parent directory
    get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
    get_filename_component(FOLDER_NAME ${PARENT_DIR} NAME)    

    # Gather all c and h files in this directory
    file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

    # Add executable. Make sure it is in WIN32
    list(APPEND SOURCE_FILES ${CT_SOURCES})

    if(UNIX)
        add_executable(${PROJECT_NAME} ${SOURCE_FILES})
        target_link_libraries(${PROJECT_NAME}  PRIVATE unity cgclib)
    endif()

    if(WIN32)
       add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})

        # Add Libraries
        target_link_libraries(${PROJECT_NAME}  PRIVATE unity cgclib user32 gdi32)

        # Setup Linker to find the main and set the proper system.
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_DEBUG "/ENTRY:mainCRTStartup /SUBSYSTEM:CONSOLE")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_MINSIZEREL "/ENTRY:mainCRTStartup /SUBSYSTEM:CONSOLE")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "/ENTRY:mainCRTStartup /SUBSYSTEM:CONSOLE /LTCG /INCREMENTAL:NO")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/ENTRY:mainCRTStartup /SUBSYSTEM:CONSOLE /LTCG /INCREMENTAL:NO")
    endif()
    # Assuming you have a subproject in a known path
    set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR})

    # Absolute path to your source directory
    set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR})

    # Compute the relative path from the build directory
    file(RELATIVE_PATH REL_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR} ${SRC_PATH})

    # Pass it as a define to your target
    target_compile_definitions(${PROJECT_NAME} PRIVATE REL_SRC_PATH=\"${REL_SRC_PATH}\")


    # Add Project to folder.
    set_target_properties(${PROJECT_NAME}  PROPERTIES FOLDER ${FOLDER_NAME})    
endfunction()