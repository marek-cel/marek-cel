cmake_minimum_required(VERSION 3.22)

################################################################################

project(HelloWorld)

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

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(glfw3 3.3 REQUIRED)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

################################################################################

include_directories(. ./src)

################################################################################

set(SOURCES
    src/main.cpp
    src/Utils.cpp
    src/WindowGL.cpp
)

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

set(LIBS
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    glfw
)

target_link_libraries(${PROJECT_NAME} ${LIBS})

