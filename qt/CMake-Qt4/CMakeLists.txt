cmake_minimum_required( VERSION 2.8 )

project( qtcmake )

################################################################################

# Find includes in corresponding build directories
set( CMAKE_INCLUDE_CURRENT_DIR ON )
# Instruct CMake to run moc automatically when needed
set( CMAKE_AUTOMOC ON )
# Create code from a list of Qt designer ui files
set( CMAKE_AUTOUIC ON )

################################################################################

# Find the Qt library
find_package( Qt4 REQUIRED QtGui )
include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )

################################################################################

add_subdirectory( gui )

################################################################################

add_executable( ${PROJECT_NAME} WIN32
    main.cpp )

################################################################################

target_link_libraries( ${PROJECT_NAME}

    gui

    -Wl,--start-group

    Qt4::QtGui

    -Wl,--end-group )
