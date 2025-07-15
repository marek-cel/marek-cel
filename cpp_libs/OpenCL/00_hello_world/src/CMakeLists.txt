set(TARGET_NAME ${PROJECT_NAME})

################################################################################

set(SOURCES
    main.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    ${OPENCL_LIBRARIES}
)

target_link_libraries(${TARGET_NAME}
    ${LIBS}
)
