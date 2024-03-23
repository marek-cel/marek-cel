#include <SceneRoot.h>

#include <iostream>

#include <osg/Geode>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

#include <QFile>
#include <QTextStream>

SceneRoot::SceneRoot()
{
    _root = new osg::Group();

    _center = new osg::Group();
    _root->addChild(_center.get());

    osg::ref_ptr<osg::StateSet> stateSet = _root->getOrCreateStateSet();

    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );

    createScene();
}

void SceneRoot::createScene()
{
    createLight();
    createBox(osg::Vec3(-6.0, 0.0, 0.0));
    createSphere(osg::Vec3(6.0, 0.0, 0.0));
}

void SceneRoot::createLight()
{
    osg::ref_ptr<osg::PositionAttitudeTransform> lightPat = new osg::PositionAttitudeTransform();
    _root->addChild(lightPat.get());

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();
    lightPat->addChild(lightSource.get());

    osg::ref_ptr<osg::Light> lightSun = new osg::Light();

    lightSun->setLightNum(0);

    osg::Vec4 color(1.0, 1.0, 1.0, 1.0);
    osg::Vec3d position(6.0, -2.0, 4.0);

    lightSun->setPosition(osg::Vec4d(position, 1.0));
    lightPat->setPosition(position);

    lightSun->setAmbient  ( color );
    lightSun->setDiffuse  ( color );
    lightSun->setSpecular ( color );

    lightSun->setConstantAttenuation(1.0);

    lightSource->setLight(lightSun.get());

    lightSource->setLocalStateSetModes(osg::StateAttribute::ON);
    lightSource->setStateSetModes(*_root->getOrCreateStateSet(), osg::StateAttribute::ON);
}

void SceneRoot::createBox(osg::Vec3 pos)
{
    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
    _root->addChild(pat.get());

    pat->setPosition(pos);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    pat->addChild(geode.get());

    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3f(), 10.0, 10.0, 10.0);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(box.get());
    shape->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
    //shape->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
    geode->addDrawable(shape.get());

    osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();

    std::string vertCode = readShaderFromFile(":/shaders/shader.vert");
    std::string fragCode = readShaderFromFile(":/shaders/shader.frag");
    //std::cout << "shader.vert:\n" << vertCode;
    //std::cout << "shader.frag:\n" << fragCode;
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode.c_str()));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode.c_str()));
    stateSet->setAttributeAndModes(program.get());
}

void SceneRoot::createSphere(osg::Vec3 pos)
{
    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
    _root->addChild(pat.get());

    pat->setPosition(pos);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    pat->addChild(geode.get());

    osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(osg::Vec3f(), 5.0);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(sphere.get());
    //shape->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
    shape->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
    geode->addDrawable(shape.get());

    osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();

    std::string vertCode = readShaderFromFile(":/shaders/shader.vert");
    std::string fragCode = readShaderFromFile(":/shaders/shader.frag");
    //std::cout << "shader.vert:\n" << vertCode;
    //std::cout << "shader.frag:\n" << fragCode;
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode.c_str()));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode.c_str()));
    stateSet->setAttributeAndModes(program.get());
}

std::string SceneRoot::readShaderFromFile(const char* path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ts(&file);
    QString code = ts.readAll();
    return code.toStdString();
}
