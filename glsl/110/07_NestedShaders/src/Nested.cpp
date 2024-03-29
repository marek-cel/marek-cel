#include <Nested.h>

#include <iostream>

#include <osg/Geode>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

#include <osgDB/ReadFile>

#include <QFile>
#include <QTextStream>

#include <utils.h>

Nested::Nested()
{
    _root = new osg::Group();
    createScene();
}

void Nested::createScene()
{
    createBox(osg::Vec3(-6.0, 0.0, 0.0));
    createSphere(osg::Vec3(6.0, 0.0, 0.0));
}

void Nested::createBox(osg::Vec3 pos)
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

    osg::ref_ptr<osg::Texture2D> texture = readTextureFromFile("../../../data/baby_letter_blobk_b.jpg");
    if ( texture.valid() )
    {
        stateSet->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    std::string vertCode = readShaderFromFile(":/shaders/shader_nested.vert");
    std::string fragCode = readShaderFromFile(":/shaders/shader_nested.frag");
    //std::cout << "shader.vert:\n" << vertCode;
    //std::cout << "shader.frag:\n" << fragCode;
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode.c_str()));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode.c_str()));
    stateSet->setAttributeAndModes(program.get());
    stateSet->addUniform(new osg::Uniform("texture0", 0));
}


void Nested::createSphere(osg::Vec3 pos)
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

    osg::ref_ptr<osg::Texture2D> texture0 = readTextureFromFile("../../../data/land_shallow_topo_1024.jpg");
    if ( texture0.valid() )
    {
        stateSet->setTextureAttributeAndModes(0, texture0, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    std::string vertCode = readShaderFromFile(":/shaders/shader_nested.vert");
    std::string fragCode = readShaderFromFile(":/shaders/shader_nested.frag");
    //std::cout << "shader.vert:\n" << vertCode;
    //std::cout << "shader.frag:\n" << fragCode;
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode.c_str()));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode.c_str()));
    stateSet->setAttributeAndModes(program.get());
    stateSet->addUniform(new osg::Uniform("texture0", 0));
}
