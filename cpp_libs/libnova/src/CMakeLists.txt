set(TARGET_NAME ${PROJECT_NAME})

################################################################################

set(SOURCES
    main.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    nova
)

target_link_libraries(${TARGET_NAME} ${LIBS})
