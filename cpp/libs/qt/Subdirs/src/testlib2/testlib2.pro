TEMPLATE = lib

################################################################################

DESTDIR = $$PWD/../../lib
TARGET = testlib2

VERSION = 1.0.0

################################################################################

unix: target.path = /usr/local/lib
!isEmpty(target.path): INSTALLS += target

################################################################################

CONFIG += c++17

################################################################################

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

################################################################################

HEADERS += \
    $$PWD/TestLib2.h

SOURCES += \
    $$PWD/TestLib2.cpp

