QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

################################################################################

DESTDIR = $$PWD/bin
TARGET = sdl-haptic

################################################################################

CONFIG += c++17 object_parallel_to_source

################################################################################

win32: CONFIG(release, debug|release): QMAKE_CXXFLAGS += -O2
unix:  CONFIG(release, debug|release): QMAKE_CXXFLAGS += -O2

win32: QMAKE_LFLAGS += /INCREMENTAL:NO

################################################################################

DEFINES += QT_DEPRECATED_WARNINGS

greaterThan(QT_MAJOR_VERSION, 4):win32: DEFINES += USE_QT5

win32: DEFINES += \
    NOMINMAX \
    WIN32 \
    _WINDOWS \
    _CRT_SECURE_NO_DEPRECATE \
    _SCL_SECURE_NO_WARNINGS \
    _USE_MATH_DEFINES

win32: CONFIG(release, debug|release): DEFINES += NDEBUG
win32: CONFIG(debug, debug|release):   DEFINES += _DEBUG

unix: CONFIG(debug, debug|release):   DEFINES += _DEBUG

unix: DEFINES += _LINUX_

################################################################################

INCLUDEPATH += ./src

unix: INCLUDEPATH += \
    /usr/include/SDL2/

win32: INCLUDEPATH += \
    $(OSG_ROOT)/include/

################################################################################

LIBS += \
    -L$$PWD/../lib

unix: LIBS += \
    -L/lib \
    -L/usr/lib \
    -L/usr/local/lib

win32: LIBS += \
    -L$(OSG_ROOT)/lib

unix: LIBS += \
    -lSDL2

################################################################################

include($$PWD/src/main.pri)
