set(TARGET_NAME ${PROJECT_NAME})

################################################################################

set(MOC_FILES
    Widget.h
)

set(UIC_FILES
    Widget.ui
)

set(SOURCES
    ${MOC_FILES}
    ${UIC_FILES}
    main.cpp
    Widget.cpp
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

qt5_use_modules(${TARGET_NAME} Widgets OpenGL)
