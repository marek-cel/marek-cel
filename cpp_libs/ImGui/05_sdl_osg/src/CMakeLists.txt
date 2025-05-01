set(TARGET_NAME ${PROJECT_NAME})

################################################################################

add_subdirectory(cgi)
add_subdirectory(gui)

################################################################################

set(SOURCES
    main.cpp
    remapKeysFromSdlToOsg.cpp
)

if( WIN32 )
    ENABLE_LANGUAGE(RC)
    set(SOURCES mc-sim.rc ${SOURCES})
endif()

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    ${LIBXML2_LIBRARIES}
    ${OPENSCENEGRAPH_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${SDL2_LIBRARIES}
)

target_link_libraries(${TARGET_NAME}
    $<TARGET_OBJECTS:cgi>
    $<TARGET_OBJECTS:gui>
    imgui
    ${LIBS}
)
