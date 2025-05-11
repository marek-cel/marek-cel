cmake_minimum_required(VERSION 3.22)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_STRING
    ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
)

project(project VERSION ${PROJECT_VERSION_STRING})

################################################################################

include(FetchContent)

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
    endif()
elseif(WIN32)
    add_definitions(-DWIN32)
    add_definitions(-D_WINDOWS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_USE_MATH_DEFINES)
    add_definitions(-DNOMINMAX)
endif()

################################################################################

if(UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    include_directories(${GTK3_INCLUDE_DIRS})
endif()

################################################################################

FetchContent_Declare(
    nativefiledialog
    GIT_REPOSITORY https://github.com/mlabbe/nativefiledialog.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(nativefiledialog)

include_directories(${nativefiledialog_SOURCE_DIR}/src/include)

set(NATIVEFILEDIALOG_SOURCES
    ${nativefiledialog_SOURCE_DIR}/src/nfd_common.c
)
if(UNIX)
    set(NATIVEFILEDIALOG_SOURCES
        ${NATIVEFILEDIALOG_SOURCES}
        ${nativefiledialog_SOURCE_DIR}/src/nfd_gtk.c
    )
endif()
if(WIN32)
    set(NATIVEFILEDIALOG_SOURCES
        ${NATIVEFILEDIALOG_SOURCES}
        ${nativefiledialog_SOURCE_DIR}/src/nfd_win.cpp
    )
endif()
add_library(nfd STATIC ${NATIVEFILEDIALOG_SOURCES})

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

include_directories(./src)

################################################################################

add_subdirectory(src)
