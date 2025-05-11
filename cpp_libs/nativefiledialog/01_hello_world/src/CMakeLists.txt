set(TARGET_NAME ${PROJECT_NAME})

################################################################################

set(SOURCES
    main.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    nfd
    ${GTK3_LIBRARIES}
)

target_link_libraries(${TARGET_NAME}
    ${LIBS}
)
