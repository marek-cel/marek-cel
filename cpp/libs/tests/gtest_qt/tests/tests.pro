TEMPLATE = app

################################################################################

DESTDIR = $$PWD/../bin
TARGET = tests

################################################################################

CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

################################################################################

unix: QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0

################################################################################

DEFINES += QT_DEPRECATED_WARNINGS GTEST_LANG_CXX11

################################################################################

INCLUDEPATH += ./ ../src

win32: INCLUDEPATH += \
    $(GTEST_DIR)/include

################################################################################

unix: LIBS += \
    -lgcov --coverage \
    -lgtest \
    -lgtest_main \
    -pthread

win32: LIBS += \
    -L$(GTEST_DIR)/lib \
    -lgtest \
    -lgtest_main

################################################################################

include(tests.pri)
include(../src/src.pri)
