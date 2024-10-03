add_subdirectory(cgi)

################################################################################

set(CPP_FILES
    main.cpp
)

set(SOURCES ${CPP_FILES})

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

if(WIN32)
    set(LIBS
        ${LIBXML2_LIBRARIES}
        ${OPENSCENEGRAPH_LIBRARIES}
        ${OPENGL_LIBRARIES}
        sfml-window
    )
endif()

if(UNIX)
    set(LIBS
        ${LIBXML2_LIBRARIES}
        ${OPENSCENEGRAPH_LIBRARIES}
        ${OPENGL_LIBRARIES}
        sfml-window
    )
endif()

target_link_libraries(${PROJECT_NAME}
    cgi
    ${LIBS}
)

