cmake_minimum_required(VERSION 3.22)

project(HelloVSG)

################################################################################

include(FetchContent)
include(GNUInstallDirs)

################################################################################

set(FETCHCONTENT_QUIET FALSE)

################################################################################

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

################################################################################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

################################################################################

set(DOWNLOADS_DIR         ${PROJECT_BINARY_DIR}/downloads)
set(COMPONENTS_DIR        ${PROJECT_BINARY_DIR}/components)
set(FETCHCONTENT_BASE_DIR ${COMPONENTS_DIR})

################################################################################

if(UNIX)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        add_definitions(-D__linux__)
    endif()
elseif(WIN32)
    add_definitions(-DWIN32)
    add_definitions(-D_WINDOWS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_USE_MATH_DEFINES)
    add_definitions(-DNOMINMAX)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    add_definitions(-D_DEBUG)
endif()

################################################################################

if(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++20")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG   "-W1")
    set(CMAKE_CXX_FLAGS_RELEASE "-W1 -O2")
    if (MSVC_VERSION GREATER_EQUAL "1930")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++20" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++20")
        endif()
    endif()
endif()

################################################################################

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

################################################################################
#
# VulkanSceneGraph
#
OPTION(BUILD_VulkanSceneGraph "Build VulkanSceneGraph" ON)
if (${BUILD_VulkanSceneGraph})
    FetchContent_Declare(vsg
        GIT_REPOSITORY https://github.com/vsg-dev/VulkanSceneGraph.git
        GIT_TAG "master"
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(vsg ${glslang_DEPENDENCY})
    set(vsg_DEPENDENCY vsg)
    include_directories(${vsg_SOURCE_DIR}/include)
endif()

################################################################################
#
# osg2vsg, only build if OpenSceneGraph is installed
#
find_package(OpenSceneGraph QUIET)
OPTION(BUILD_osg2vsg "Build osg2vsg" ${OpenSceneGraph_FOUND})
if (${BUILD_osg2vsg})
    FetchContent_Declare(osg2vsg
        GIT_REPOSITORY "https://github.com/vsg-dev/osg2vsg.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(osg2vsg ${vsg_DEPENDENCY})
    set(osg2vsg_DEPENDENCY osg2vsg)
endif()

################################################################################
#
# assimp
#
OPTION(BUILD_assimp "Build assimp" ON)
if (${BUILD_assimp})

    set(assimp_VERSION "5.4.3")
    # set(assimp_VERSION "master")

    FetchContent_Declare(assimp
        GIT_REPOSITORY "https://github.com/assimp/assimp.git"
        GIT_TAG "v${assimp_VERSION}"
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(assimp)

    # add definitions to enable locally built assimp lib to be recognized by vsgXchange
    # add_library(assimp::assimp ALIAS assimp)
    # add_library(assimp)
    export(TARGETS assimp FILE assimp-targets.cmake)
    set(assimp_FOUND TRUE CACHE INTERNAL "assimp found.")
    set(CMAKE_DISABLE_FIND_PACKAGE_assimp TRUE CACHE INTERNAL "Disable find_package(assimp) as it's not necessary.")

    set(assimp_DEPENDENCY assimp)
endif()

##############################################################################################################
#
# vsgXchange
#
OPTION(BUILD_vsgXchange "Build vsgXchange" ON)
if (${BUILD_vsgXchange})
    FetchContent_Declare(vsgxchange
        GIT_REPOSITORY https://github.com/vsg-dev/vsgXchange.git
        GIT_TAG master
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(vsgxchange ${vsg_DEPENDENCY} ${osg2vsg_DEPENDENCY} ${assimp_DEPENDENCY})
    set(vsgXchange_DEPENDENCY vsgxchange)
endif()

##############################################################################################################
#
# vsgImGui
#
OPTION(BUILD_vsgImGui "Build vsgImGui" ON)
if (${BUILD_vsgImGui})
    FetchContent_Declare(vsgimgui
        GIT_REPOSITORY "https://github.com/vsg-dev/vsgImGui.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(vsgimgui ${vsg_DEPENDENCY} )
endif()

################################################################################

include_directories(. ./src)

################################################################################

add_subdirectory(src)
