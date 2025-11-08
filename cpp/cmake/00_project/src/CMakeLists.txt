set(TARGET_NAME ${PROJECT_NAME})

################################################################################

include_directories(.)

################################################################################

set(SOURCES
    main.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS

)

target_link_libraries(${TARGET_NAME}
    ${LIBS}
)
