QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

################################################################################

DESTDIR = ../bin
TARGET = test

################################################################################

CONFIG += c++17

################################################################################

DEFINES += QT_DEPRECATED_WARNINGS

################################################################################

SOURCES += \
    MyClass.cpp \
    MyQObject.cpp \
    main.cpp

HEADERS += \
    MyClass.h \
    MyQObject.h

FORMS += \
