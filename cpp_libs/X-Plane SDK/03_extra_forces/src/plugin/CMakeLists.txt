set(TARGET_NAME plugin)

################################################################################

set(SOURCES
    plugin.cpp
    ../UdpSocket.cpp
)

################################################################################

if(UNIX)
    add_library(${PROJECT_NAME} SHARED ${SOURCES})
elseif(WIN32)
    add_library(${PROJECT_NAME} MODULE ${SOURCES})
endif()

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.xpl")
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES SUFFIX "")

################################################################################

set(LIBS
)

target_link_libraries(${PROJECT_NAME} ${LIBS})

