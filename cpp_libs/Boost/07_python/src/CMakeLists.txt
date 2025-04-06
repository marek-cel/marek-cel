set(CPP_FILES
    main.cpp
)

set(SOURCES ${CPP_FILES})

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

if(WIN32)
    set(LIBS
        ${Boost_LIBRARIES}
        ${Python3_LIBRARIES}
    )
endif()

if(UNIX)
    set(LIBS
        ${Boost_LIBRARIES}
        ${Python3_LIBRARIES}
    )
endif()

target_link_libraries(${PROJECT_NAME}
    ${LIBS}
)

