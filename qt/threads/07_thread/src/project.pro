QT += core gui

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
    MyThreadTimer.cpp \
    MyThreadLoop.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h \
    MyThreadTimer.h \
    MyThreadLoop.h

FORMS += \
    MainWindow.ui
