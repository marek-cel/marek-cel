cmake_minimum_required(VERSION 3.22)

################################################################################

project(ImGui)

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
    set(CMAKE_CXX_FLAGS "-Wall -std=c++17")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG   "-Wall -std=c++1z")
    set(CMAKE_CXX_FLAGS_RELEASE "-Wall -std=c++1z -O2")
    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++17")
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

#find_library(IMGUI_LIBRARY NAMES imgui)
#include_directories("/usr/include/imgui")

################################################################################

find_library(STB_LIBRARY NAMES stb)

################################################################################

include_directories(. ./src ./imgui ./imgui/backends ./imgui-osg/src)

################################################################################

set(SOURCES
    src/main.cpp
    src/SceneRoot.cpp
    imgui-osg/src/OsgImGuiHandler.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
)

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

set(LIBS
    ${OPENSCENEGRAPH_LIBRARIES}
    ${STB_LIBRARY}
)

target_link_libraries(${PROJECT_NAME} ${LIBS})

