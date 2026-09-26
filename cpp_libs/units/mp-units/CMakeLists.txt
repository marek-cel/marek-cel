cmake_minimum_required(VERSION 3.22)

project(units-test)

include(FetchContent)

################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

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
endif()

################################################################################
# mp-units (https://github.com/mpusz/mp-units)
#
# mp-units is normally consumed via Conan + find_package(mp-units), which is
# the officially recommended route (it pulls in the correct versions of its
# own dependencies, e.g. gsl-lite for contract checks). Since this project
# fetches it directly instead, we disable contract-checking dependencies and
# the install target so a plain FetchContent build works with no extra
# package manager. If you later switch to Conan, drop this block and use
# find_package(mp-units REQUIRED) instead.

set(MP_UNITS_BUILD_INSTALL OFF CACHE BOOL "" FORCE)
set(MP_UNITS_API_CONTRACTS "NONE" CACHE STRING "" FORCE)

FetchContent_Declare(mp-units
    GIT_REPOSITORY https://github.com/mpusz/mp-units.git
    GIT_TAG v2.5.0
    SOURCE_DIR "${CMAKE_BINARY_DIR}/mp-units"
    SOURCE_SUBDIR src)
FetchContent_MakeAvailable(mp-units)

################################################################################

if(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++20")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG   "-Wall -std=c++20")
    set(CMAKE_CXX_FLAGS_RELEASE "-Wall -std=c++20 -O2")
    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++20" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++20")
        endif()
    endif()
endif()

################################################################################

include_directories(. ./src)

################################################################################

add_subdirectory(src)

################################################################################

target_link_libraries(${PROJECT_NAME} PRIVATE mp-units::mp-units)