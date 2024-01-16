set(TARGET_NAME tests)

################################################################################

find_package(GTest REQUIRED)

################################################################################

include_directories(. ../src)

################################################################################

set(SOURCES
    ../src/ClassA.cpp
    TestClassA.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(${TARGET_NAME}
    gcov
    GTest::gtest
    GTest::gtest_main
)

################################################################################

gtest_discover_tests(${TARGET_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
