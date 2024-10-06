set(CPP_FILES
    main.cpp
)

set(SOURCES ${CPP_FILES})

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

if(WIN32)
    set(LIBS
        ${Boost_LIBRARIES}
    )
endif()

if(UNIX)
    set(LIBS
        ${Boost_LIBRARIES}
    )
endif()

target_link_libraries(${PROJECT_NAME}
    ${LIBS}
)

