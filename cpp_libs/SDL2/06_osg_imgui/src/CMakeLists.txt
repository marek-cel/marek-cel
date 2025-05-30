include_directories(./imgui ./imgui/backends)

################################################################################

add_subdirectory(cgi)
add_subdirectory(gui)

################################################################################

set(CPP_FILES
    main.cpp
    KeyMap.cpp
)

set(CPP_FILES
    ${CPP_FILES}
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/backends/imgui_impl_sdl2.cpp
)

set(SOURCES ${CPP_FILES})

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

if(WIN32)
    set(LIBS
        ${LIBXML2_LIBRARIES}
        ${OPENSCENEGRAPH_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${SDL2_LIBRARIES}
    )
endif()

if(UNIX)
    set(LIBS
        ${LIBXML2_LIBRARIES}
        ${OPENSCENEGRAPH_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${SDL2_LIBRARIES}
    )
endif()

message(STATUS "LIBS: ${LIBS}")

target_link_libraries(${PROJECT_NAME}
    cgi
    gui
    ${LIBS}
)

