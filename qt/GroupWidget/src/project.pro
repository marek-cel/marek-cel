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
    TreeItem.cpp \
    TreeModel.cpp \
    main.cpp

HEADERS += \
    MainWindow.h \
    TreeItem.h \
    TreeModel.h

FORMS += \
    MainWindow.ui
