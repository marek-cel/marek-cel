set(CPP_FILES
    main.cpp
)

set(SOURCES ${CPP_FILES})

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

if(WIN32)
    set(LIBS
        sfml-window
    )
endif()

if(UNIX)
    set(LIBS
        sfml-window
    )
endif()

target_link_libraries(${PROJECT_NAME}
    ${LIBS}
)

