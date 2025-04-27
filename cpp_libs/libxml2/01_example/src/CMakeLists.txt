
set(SOURCES
    main.cpp
)

################################################################################

# add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
${LIBXML2_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} ${LIBS})
