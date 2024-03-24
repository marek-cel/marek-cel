#include <SkyDome.h>

#include <iostream>

#include <osg/Geode>
#include <osg/ShapeDrawable>

#include <utils.h>

SkyDome::SkyDome()
{
    _root = new osg::Group();
    createScene();
}

void SkyDome::update()
{
    _uniformSunElev->set(_sunElev_rad);
}

void SkyDome::createScene()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild(geode.get());

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
    _uniformSunElev = new osg::Uniform("sunElev", 0.0f);
    stateSet->addUniform(_uniformSunElev.get());
}
