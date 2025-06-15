set(TARGET_NAME app)

################################################################################

add_subdirectory(plugin)

################################################################################

set(CPP_FILES
    main.cpp
    GUI.cpp
    UdpSocket.cpp
)

set(MOC_FILES
    GUI.h
)

set(UIC_FILES
    GUI.ui
)

################################################################################

add_executable(${TARGET_NAME} WIN32 ${CPP_FILES} ${MOC_FILES} ${UIC_FILES})

qt5_use_modules(${TARGET_NAME} Core Widgets)

set(LIBS
    ${QT_LIBRARIES}
)

target_link_libraries(${TARGET_NAME}
    ${LIBS}
)
