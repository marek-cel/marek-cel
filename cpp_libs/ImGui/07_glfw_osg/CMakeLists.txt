cmake_minimum_required(VERSION 3.22)

################################################################################

project(HelloWorld)

################################################################################

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

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(glfw3 3.3 REQUIRED)

################################################################################

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

################################################################################

find_package(OpenSceneGraph REQUIRED
    OpenThreads
    osg
    osgDB
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

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        docking
)
# FetchContent_Declare(
#     imgui
#     GIT_REPOSITORY https://github.com/ocornut/imgui.git
#     GIT_TAG        features/sdl_renderer3_multiviewports
# )
FetchContent_MakeAvailable(imgui)

include_directories(${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)

set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})

################################################################################

include_directories(. ./src)

################################################################################

set(SOURCES
    src/main.cpp
    src/SceneRoot.cpp
    src/KeyMap.cpp
    src/ImGuiEventHandler.cpp
    src/ImGuiApp.cpp
)

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

set(LIBS
    ${LIBXML2_LIBRARIES}
    ${OPENSCENEGRAPH_LIBRARIES}
    ${OPENGL_LIBRARIES}
    glfw
    imgui
)

target_link_libraries(${PROJECT_NAME} ${LIBS})

