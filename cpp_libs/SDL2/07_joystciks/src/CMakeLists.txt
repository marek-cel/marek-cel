set(CPP_FILES
    main.cpp
)

set(SOURCES ${CPP_FILES})

################################################################################

add_executable(${PROJECT_NAME} ${SOURCES})

if(WIN32)
    set(LIBS
        ${SDL2_LIBRARIES}
    )
endif()

if(UNIX)
    set(LIBS
        ${SDL2_LIBRARIES}
    )
endif()

target_link_libraries(${PROJECT_NAME}
    ${LIBS}
)

