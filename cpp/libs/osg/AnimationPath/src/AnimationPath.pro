QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

################################################################################

TARGET = ViewerQt

DESTDIR = ../bin

greaterThan(QT_MAJOR_VERSION, 4):win32: DEFINES += USE_QT5

win32: QMAKE_LFLAGS += /INCREMENTAL:NO

win32: QMAKE_CXXFLAGS += /Zc:wchar_t

win32: DEFINES += \
    WIN32 \
    _WINDOWS \
    _CRT_SECURE_NO_DEPRECATE \
    _SCL_SECURE_NO_WARNINGS \
    _USE_MATH_DEFINES

win32:CONFIG(release, debug|release): DEFINES += \
    NDEBUG

win32:CONFIG(debug, debug|release): DEFINES += \
    _DEBUG

unix: DEFINES += _LINUX_

################################################################################

win32: INCLUDEPATH += \
    $(OSG_ROOT)/include/

unix: INCLUDEPATH += \

################################################################################

#greaterThan(QT_MAJOR_VERSION, 4)
#{
#    win32:CONFIG(release, debug|release): LIBS += \
#        -lnvcore
#    win32:CONFIG(debug, debug|release): LIBS += \
#        -lnvcore_d
#}

win32: LIBS += \
    -L$(OSG_ROOT)/lib \
    -lopengl32

win32:CONFIG(release, debug|release): LIBS += \
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

win32:CONFIG(debug, debug|release): LIBS += \
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
    -L/lib \
    -L/usr/lib \
    -L/usr/local/lib \
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

################################################################################

HEADERS += \
    AnimationPathCallback.h \
    GraphicsWindowQt.h \
    KeyMap.h \
    MainWindow.h \
    SceneRoot.h \
    WidgetCGI.h

SOURCES += \
    AnimationPathCallback.cpp \
    GraphicsWindowQt.cpp \
    KeyMap.cpp \
    main.cpp \
    MainWindow.cpp \
    SceneRoot.cpp \
    WidgetCGI.cpp

FORMS += \
    MainWindow.ui
