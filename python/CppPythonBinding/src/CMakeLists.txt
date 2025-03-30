set(CPP_FILES
    main.cpp
)

set(SOURCES ${CPP_FILES})

################################################################################

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
    ${Python3_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} ${LIBS})
