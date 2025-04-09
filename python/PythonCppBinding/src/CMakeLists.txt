set(TARGET_NAME foobar)

################################################################################

if(WIN32)
    if(BUILD_SHARED_LIBS)
        add_definitions(-DFOOBAR_DLL_EXPORTS)
    endif()
endif()

################################################################################

set(HEADERS
    foobar.h
)

set(SOURCES
    foobar.cpp
)

################################################################################

add_library(${TARGET_NAME} ${SOURCES})

################################################################################

target_link_libraries(${TARGET_NAME} ${LIBS})
