set(TARGET_NAME math_plugin)

################################################################################

set(SOURCES
    math_plugin.cpp
)

################################################################################

add_library(${TARGET_NAME} SHARED ${SOURCES})

target_link_libraries(${TARGET_NAME} ${LIBS})

