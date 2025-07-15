set(TARGET_NAME ${PROJECT_NAME})

################################################################################

set(MOC_FILES
    MainWindow.h
)

set(UIC_FILES
    MainWindow.ui
)

set(SOURCES
    ${MOC_FILES}
    ${UIC_FILES}
    main.cpp
    MainWindow.cpp
    Visualization.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
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
