cmake_minimum_required(VERSION 3.22)

################################################################################

project(AnimatedSwitch)

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

if (BUILD_TESTING)
    add_definitions(-D_GTEST_)
    add_definitions(-D_TESTS_)
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

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(WIN32)
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets OpenGL)
endif()

if(UNIX)
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets OpenGL)
endif()

find_package(OpenSceneGraph REQUIRED
    OpenThreads
    osg
    osgAnimation
    osgDB
    osgGA
    osgParticle
    osgSim
    osgText
    osgUtil
    osgViewer
    osgWidget
)

################################################################################

include_directories(. ./src ${OPENSCENEGRAPH_INCLUDE_DIRS})


################################################################################

set(CPP_FILES
    src/main.cpp
    src/GraphicsWindowQt.cpp
    src/KeyMap.cpp
    src/MainWindow.cpp
    src/SceneRoot.cpp
    src/WidgetCGI.cpp
    src/SwitchingCallback.cpp
)

set(MOC_SRC_FILES
    src/MainWindow.h
    src/WidgetCGI.h
)

set(UIC_SRC_FILES
    src/MainWindow.ui
)

set(RCC_SRC_FILES

)

set(SOURCES ${CPP_FILES} ${MOC_SRC_FILES} ${MOC_SRC_FILES} ${UIC_SRC_FILES} ${RCC_SRC_FILES})

if( WIN32 )
    ENABLE_LANGUAGE(RC)
    set(SOURCES mc-sim.rc ${SOURCES})
endif()

################################################################################

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

qt5_use_modules(${PROJECT_NAME} Core Widgets OpenGL)

if(WIN32)
    set(LIBS
        ${QT_LIBRARIES}
        ${OPENSCENEGRAPH_LIBRARIES}
    )
endif()

if(UNIX)
    set(LIBS
        ${QT_LIBRARIES}
        ${OPENSCENEGRAPH_LIBRARIES}
    )
endif()

target_link_libraries(${PROJECT_NAME} ${LIBS})

