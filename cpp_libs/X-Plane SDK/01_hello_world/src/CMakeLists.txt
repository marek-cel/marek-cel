set(SOURCES
    hello_world.cpp
)

set(LIBS

)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${LIBS})

