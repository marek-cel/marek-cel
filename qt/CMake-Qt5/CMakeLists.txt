cmake_minimum_required( VERSION 3.5 )

project( qtcmake )

################################################################################

set( CMAKE_INCLUDE_CURRENT_DIR ON )

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )

set(CMAKE_CXX_STANDARD 11 )
set(CMAKE_CXX_STANDARD_REQUIRED ON )

################################################################################

find_package( Qt5 COMPONENTS Widgets REQUIRED )

################################################################################

add_subdirectory( gui )

################################################################################

add_executable( ${PROJECT_NAME} WIN32
    main.cpp )

################################################################################

target_link_libraries( ${PROJECT_NAME}

    gui

    -Wl,--start-group

    Qt5::Widgets

    -Wl,--end-group )
