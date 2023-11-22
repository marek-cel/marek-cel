cmake_minimum_required(VERSION 3.5)

project(CppJenkinsDockerExample)

################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

################################################################################

include(CTest)
include(GoogleTest)

enable_testing()

################################################################################

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

if (BUILD_TESTING)
    add_definitions(-D_GTEST_)
    add_definitions(-D_TESTS_)
endif()

################################################################################

set(CMAKE_CXX_FLAGS "-Wall -O3 -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fno-default-inline -fno-inline -fno-inline-small-functions -fprofile-arcs -ftest-coverage -pedantic")

################################################################################

find_package(Boost REQUIRED)

################################################################################

include_directories(./src)

################################################################################

set(CPP_FILES
    src/main.cpp
    src/ClassA.cpp
)

set(SOURCES ${CPP_FILES})

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    Boost::boost
)

################################################################################

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()