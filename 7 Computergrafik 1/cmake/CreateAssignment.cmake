function(CreateAssignment)
    # Base name of the current directory
    get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

    # Base name of the parent directroy
    get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
    get_filename_component(FOLDER_NAME ${PARENT_DIR} NAME)    

    # Gather all c and h files in this directory
    file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

    if(UNIX)
        add_executable(${PROJECT_NAME} ${SOURCE_FILES})
        target_link_libraries(${PROJECT_NAME}  PRIVATE cgclib )
    endif()

    if(WIN32)
        # We need to link against OpenMP
        find_package(OpenMP REQUIRED)
        # Add executable. Make sure it is in WIN32
        add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})

        # Add Libraries
        target_link_libraries(${PROJECT_NAME}  PRIVATE cgclib user32 gdi32 OpenMP::OpenMP_C)

        # Setup Linker to find the main and set the proper system.
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_DEBUG "/ENTRY:mainCRTStartup /SUBSYSTEM:CONSOLE")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_MINSIZEREL "/ENTRY:mainCRTStartup /SUBSYSTEM:CONSOLE")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "/ENTRY:mainCRTStartup /SUBSYSTEM:CONSOLE /LTCG /INCREMENTAL:NO")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/ENTRY:mainCRTStartup /SUBSYSTEM:CONSOLE /LTCG /INCREMENTAL:NO")

        # Add Project to folder.
        set_target_properties(${PROJECT_NAME}  PROPERTIES FOLDER ${FOLDER_NAME})            
    endif()
endfunction()