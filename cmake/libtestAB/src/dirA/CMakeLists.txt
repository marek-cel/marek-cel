set( DIRA_HEADERS
    ClassA.h
)

add_library( testDirA SHARED

    ClassA.cpp
)

include(GNUInstallDirs)

set_target_properties( testDirA PROPERTIES PUBLIC_HEADER "${DIRA_HEADERS}" )

install( TARGETS testDirA
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testAB/DirA
)
