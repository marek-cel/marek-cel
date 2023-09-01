cmake_minimum_required( VERSION 3.5 )

project( basic )

################################################################################

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

################################################################################

set( CMAKE_INCLUDE_CURRENT_DIR ON )

set(CMAKE_CXX_STANDARD 17 )
set(CMAKE_CXX_STANDARD_REQUIRED ON )

################################################################################

# add_definitions( -DSIM_CONSOLE_OUTPUT )
# add_definitions( -DSIM_OSG_DEBUG_INFO )
add_definitions( -DSIM_INTERSECTIONS )
# add_definitions( -DSIM_LOCAL_DATA_DIR )
add_definitions( -DSIM_SKYDOME_SCALING )
add_definitions( -DSIM_USE_THREADS )
add_definitions( -DSIM_VERTICALSYNC )

if( UNIX )
    add_definitions( -D_LINUX_ )
elseif( WIN32 )
    add_definitions( -DWIN32 )
    add_definitions( -D_WINDOWS )
    add_definitions( -D_CRT_SECURE_NO_DEPRECATE )
    add_definitions( -D_SCL_SECURE_NO_WARNINGS )
    add_definitions( -D_USE_MATH_DEFINES )
endif()

################################################################################

set( CMAKE_CXX_FLAGS "-Wall -O3 -std=c++17" )

################################################################################

include_directories( . )

################################################################################

set( CPP_FILES
    main.cpp
)

set( SOURCES ${CPP_FILES} )

################################################################################

add_executable( ${PROJECT_NAME} WIN32 ${SOURCES} )
