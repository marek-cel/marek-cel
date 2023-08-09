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
    CollapsableWidget.cpp \
    MainWindow.cpp \
    main.cpp

HEADERS += \
    CollapsableWidget.h \
    MainWindow.h

FORMS += \
    CollapsableWidget.ui \
    MainWindow.ui
