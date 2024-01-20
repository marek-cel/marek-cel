DEPLOYMENTFOLDERS =

symbian:TARGET.UID3 = 0xEE8DE40B

symbian:TARGET.CAPABILITY +=

CONFIG      += mobility
MOBILITY    += sensors

QT          += opengl core gui declarative

SOURCES     += main.cpp \
            mainwindow.cpp \
            mcel_sensor.cpp \
            mcel_declarative.cpp \
            mcel_adi.cpp

HEADERS     += mainwindow.h \
            mcel_sensor.h \
            mcel_declarative.h \
            mcel_adi.h

FORMS       += mainwindow.ui

include(deployment.pri)
qtcAddDeployment()

RESOURCES += ADI_Touch_2.qrc

OTHER_FILES += \
    qml/info.qml
