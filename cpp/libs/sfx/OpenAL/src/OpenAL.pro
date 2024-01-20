QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

################################################################################

DESTDIR = ../bin
TARGET = openal

################################################################################

CONFIG += c++11

################################################################################

DEFINES += QT_DEPRECATED_WARNINGS

LIBS += \
    -lopenal \
    -lalut

################################################################################

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h

FORMS += \
    MainWindow.ui
