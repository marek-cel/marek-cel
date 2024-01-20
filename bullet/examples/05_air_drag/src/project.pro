QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

################################################################################

DESTDIR = $$PWD/../bin
TARGET = exec

################################################################################

CONFIG += c++17

################################################################################

DEFINES += QT_DEPRECATED_WARNINGS

greaterThan(QT_MAJOR_VERSION, 4):win32: DEFINES += USE_QT5

################################################################################

INCLUDEPATH += ./ /usr/include/bullet

win32: INCLUDEPATH += \
    $(OSG_ROOT)/include/

################################################################################

#unix: LIBS += -Wl,--start-group

win32: LIBS += \
    -L$(OSG_ROOT)/lib

win32: CONFIG(release, debug|release): LIBS += \
    -lOpenThreads \
    -losg \
    -losgDB \
    -losgGA \
    -losgParticle \
    -losgSim \
    -losgText \
    -losgUtil \
    -losgViewer \
    -losgWidget

win32: CONFIG(debug, debug|release): LIBS += \
    -lOpenThreadsd \
    -losgd \
    -losgDBd \
    -losgGAd \
    -losgParticled \
    -losgSimd \
    -losgTextd \
    -losgUtild \
    -losgViewerd \
    -losgWidgetd

unix: LIBS += \
    -L/lib

unix: LIBS += \
    -lBulletCollision \
    -lBulletDynamics \
    -lLinearMath \
    -lOpenThreads \
    -losg \
    -losgDB \
    -losgGA \
    -losgParticle \
    -losgSim \
    -losgText \
    -losgUtil \
    -losgViewer \
    -losgWidget

#unix: LIBS += -Wl,--end-group

################################################################################

HEADERS += \
    $$PWD/defs.h

SOURCES += \
    $$PWD/main.cpp

################################################################################

include($$PWD/cgi/cgi.pri)
include($$PWD/gui/gui.pri)
