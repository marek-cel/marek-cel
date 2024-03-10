TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

################################################################################

TARGET = Shader01

################################################################################

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

#shaderFragTarget.target = shader_frag.cpp
#shaderFragTarget.depends = FORCE
#shaderFragTarget.commands = osg2cpp --shader shader.frag

#shaderVertTarget.target = shader_vert.cpp
#shaderVertTarget.depends = FORCE
#shaderVertTarget.commands = osg2cpp --shader shader.vert

#PRE_TARGETDEPS += \
#    shader_frag.cpp \
#    shader_vert.cpp

#QMAKE_EXTRA_TARGETS += \
#    shaderFragTarget \
#    shaderVertTarget

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
    -losgText \
    -losgUtil \
    -losgViewer \
    -losgWidget

################################################################################

HEADERS += \
    SceneRoot.h

SOURCES += \
    main.cpp \
    SceneRoot.cpp \
    shader_frag.cpp \
    shader_vert.cpp

OTHER_FILES += \
    shader.frag \
    shader.vert
