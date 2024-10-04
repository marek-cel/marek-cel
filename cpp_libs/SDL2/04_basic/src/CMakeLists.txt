set(CPP_FILES
    main.cpp
    Game.cpp
)

set(SOURCES ${CPP_FILES})

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

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

message(STATUS "LIBS: ${LIBS}")

target_link_libraries(${PROJECT_NAME}
    ${LIBS}
)

