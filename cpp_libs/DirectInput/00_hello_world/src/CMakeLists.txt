add_subdirectory(gui)

################################################################################

set(SOURCES
    main.cpp
    ${MOC_SRC_FILES}
)

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

qt5_use_modules(${PROJECT_NAME} Core Widgets)

#     set(LIBS
#         ${Boost_LIBRARIES}
#     )

target_link_libraries(${PROJECT_NAME}
    gui
    ${LIBS}
)
