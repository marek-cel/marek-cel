QT += testlib
QT -= gui

################################################################################

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

################################################################################

TARGET = qtest

################################################################################

DEFINES += QT_DEPRECATED_WARNINGS

unix:  DEFINES += _LINUX_
win32: DEFINES += WIN32

################################################################################

INCLUDEPATH += ./

################################################################################

HEADERS += \
    AutoTest.h \
    BarClass.h \
    FooClass.h

SOURCES += \
    main.cpp \
    test_bar_class.cpp \
    test_foo_class.cpp

################################################################################

DEFINES += SRCDIR=\\\"$$PWD/\\\"
