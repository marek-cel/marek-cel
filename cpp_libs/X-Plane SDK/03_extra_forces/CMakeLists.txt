cmake_minimum_required(VERSION 3.28)

project(extra_forces)

################################################################################

include(FetchContent)
include(GNUInstallDirs)

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

if(UNIX)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        add_definitions(-D_LINUX_)
        add_definitions(-D__linux__)
        add_definitions(-DAPL=0)
        add_definitions(-DIBM=0)
        add_definitions(-DLIN=1)
    endif()
elseif(WIN32)
    add_definitions(-DWIN32)
    add_definitions(-DAPL=0)
    add_definitions(-DIBM=1)
    add_definitions(-DLIN=0)
    add_definitions(-D_WINDOWS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_USE_MATH_DEFINES)
    add_definitions(-DNOMINMAX)
endif()

add_definitions(-DXPLM200=1)
add_definitions(-DXPLM210=1)
add_definitions(-DXPLM300=1)
add_definitions(-DXPLM301=1)
add_definitions(-DXPLM303=1)
add_definitions(-DXPLM400=1)
add_definitions(-DXPLM410=1)

################################################################################

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets HINTS $ENV{QTDIR})

################################################################################

if(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++20 -fvisibility=hidden")
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

FetchContent_Declare(
  xpsdk
  URL https://developer.x-plane.com/wp-content/plugins/code-sample-generation/sdk_zip_files/XPSDK411.zip
)
FetchContent_MakeAvailable(xpsdk)

include_directories(${xpsdk_SOURCE_DIR}/CHeaders)
include_directories(${xpsdk_SOURCE_DIR}/CHeaders/XPLM)
include_directories(${xpsdk_SOURCE_DIR}/CHeaders/Widgets)

################################################################################

include_directories(./src)

################################################################################

add_subdirectory(src)