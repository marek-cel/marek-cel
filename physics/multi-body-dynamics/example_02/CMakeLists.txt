cmake_minimum_required(VERSION 3.22)

################################################################################

project(multibody-dynamics)

################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

################################################################################

if(UNIX)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        add_definitions(-D_LINUX_)
    endif()
elseif(WIN32)
    add_definitions(-DWIN32)
    add_definitions(-D_WINDOWS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_USE_MATH_DEFINES)
endif()

################################################################################

if(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++20")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG   "-Wall")
    set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")
    if (MSVC_VERSION GREATER_EQUAL "1930")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++20" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++20")
        endif()
    endif()
endif()

################################################################################

find_package(OpenSceneGraph REQUIRED
    OpenThreads
    osg
    osgAnimation
    osgDB
    osgFX
    osgGA
    osgParticle
    osgSim
    osgText
    osgUtil
    osgViewer
    osgWidget
)

include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

################################################################################

include_directories(. ./src)

################################################################################

set(SOURCES
    src/main.cpp
    src/SceneRoot.cpp
)

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

set(LIBS
    ${OPENSCENEGRAPH_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} ${LIBS})

