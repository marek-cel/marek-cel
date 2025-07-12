set(TARGET_NAME ${PROJECT_NAME})

################################################################################

set(SOURCES
    main.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    ${Boost_LIBRARIES}
    ${VTK_LIBRARIES}
)

target_link_libraries(${TARGET_NAME}
    ${LIBS}
)

vtk_module_autoinit(
    TARGETS ${TARGET_NAME}
    MODULES ${VTK_LIBRARIES}
)