set(TARGET_NAME ${PROJECT_NAME})

################################################################################

include_directories(.)

################################################################################

# add_subdirectory(cgi)
# add_subdirectory(gui)
# add_subdirectory(hid)
# add_subdirectory(utils)

################################################################################

set(SOURCES
    main.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    ${OPENSCENEGRAPH_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

if(UNIX)
    set(LIBS
        ${LIBS}
    )
endif()

if(WIN32)
    set(LIBS
        ${LIBS}
    )
endif()

target_link_libraries(${TARGET_NAME}
    ${LIBS}
)
