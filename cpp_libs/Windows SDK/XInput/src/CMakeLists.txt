
set(CPP_FILES
    main.cpp
    MainWindow.cpp
    Controllers.cpp
)

set(MOC_SRC_FILES
    MainWindow.h
)

set(UIC_SRC_FILES
    MainWindow.ui
)

set(SOURCES
    ${CPP_FILES}
    ${MOC_SRC_FILES}
)

################################################################################

# add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})

qt5_use_modules(${PROJECT_NAME} Core Widgets)

set(LIBS
    Xinput
)

target_link_libraries(${PROJECT_NAME} ${LIBS})
