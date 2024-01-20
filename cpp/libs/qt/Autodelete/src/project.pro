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
    MainWindow.cpp \
    MyAction.cpp \
    MyDockWidget.cpp \
    MyMenu.cpp \
    MyShortcut.cpp \
    main.cpp

HEADERS += \
    MainWindow.h \
    MyAction.h \
    MyDockWidget.h \
    MyMenu.h \
    MyShortcut.h

FORMS += \
    MainWindow.ui \
    MyDockWidget.ui
