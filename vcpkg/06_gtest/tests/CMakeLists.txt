set(TARGET_NAME tests)

################################################################################

find_package(GTest CONFIG REQUIRED)

################################################################################

include_directories(. ../src)

################################################################################

set(SOURCES
    TestMyClass.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

set(LIBS
    GTest::gtest
    GTest::gtest_main
)

target_link_libraries(${TARGET_NAME} ${LIBS})
