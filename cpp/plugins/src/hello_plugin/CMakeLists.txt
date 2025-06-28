set(TARGET_NAME hello_plugin)

################################################################################

set(SOURCES
    hello_plugin.cpp
)

################################################################################

add_library(${TARGET_NAME} SHARED ${SOURCES})

target_link_libraries(${TARGET_NAME} ${LIBS})

