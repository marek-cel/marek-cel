add_subdirectory(hello_plugin)
add_subdirectory(math_plugin)

################################################################################

set(SOURCES
    main.cpp
)

################################################################################

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS

)

target_link_libraries(${PROJECT_NAME}
    ${LIBS}
)
