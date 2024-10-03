set(CPP_FILES
    main.cpp
)

set(SOURCES ${CPP_FILES})

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

if(WIN32)
    set(LIBS
        SDL2::SDL2
    )
endif()

if(UNIX)
    set(LIBS
        SDL2::SDL2
    )
endif()

target_link_libraries(${PROJECT_NAME}
    ${LIBS}
)

