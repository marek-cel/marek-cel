set( DIRB_HEADERS
    ClassB.h
)

add_library( testDirB SHARED

    ClassB.cpp
)

include(GNUInstallDirs)

set_target_properties( testDirB PROPERTIES PUBLIC_HEADER "${DIRB_HEADERS}" )

install( TARGETS testDirB
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testAB/DirB
)
