set(TARGET_NAME plugin)

################################################################################

set(SOURCES
    plugin.cpp
)

################################################################################

set(LIBS

)

add_library(${TARGET_NAME} SHARED ${SOURCES})

target_link_libraries(${TARGET_NAME} ${LIBS})

