#include <SceneRoot.h>

#include <iostream>

#include <osg/Geode>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

#include <osgDB/ReadFile>

#include <QFile>
#include <QTextStream>

#include <ComputeTangentVisitor.h>

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
    createBox(osg::Vec3(-6.0, -12.0, 0.0), false);
    createBox(osg::Vec3(-6.0,   0.0, 0.0), true, true);
    createBox(osg::Vec3(-6.0,  12.0, 0.0), true);
    createSphere(osg::Vec3(6.0, -12.0, 0.0), false);
    createSphere(osg::Vec3(6.0,   0.0, 0.0), true, true);
    createSphere(osg::Vec3(6.0,  12.0, 0.0), true);

    ComputeTangentVisitor ctv;
    ctv.setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
    _root->accept(ctv);
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

void SceneRoot::createBox(osg::Vec3 pos, bool normalMapping, bool shader2)
{
    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
    _root->addChild(pat.get());

    pat->setPosition(pos);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    pat->addChild(geode.get());

    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3f(), 10.0, 10.0, 10.0);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(box.get());
    shape->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
    //shape->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
    geode->addDrawable(shape.get());

    osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();

    osg::ref_ptr<osg::Texture2D> texture0 = readTextureFromFile("../../../data/DiamondPlate008C_1K_Color.jpg");
    if ( texture0.valid() )
    {
        stateSet->setTextureAttributeAndModes(0, texture0, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Texture2D> texture1 = readTextureFromFile("../../../data/DiamondPlate008C_1K_NormalGL.jpg");
    if ( texture1.valid() )
    {
        stateSet->setTextureAttributeAndModes(1, texture1, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Texture2D> texture2 = readTextureFromFile("../../../data/DiamondPlate008C_1K_Roughness.jpg");
    if ( texture2.valid() )
    {
        stateSet->setTextureAttributeAndModes(2, texture2, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    std::string vertCode = readShaderFromFile(":/shaders/shader.vert");
    std::string fragCode = readShaderFromFile(":/shaders/shader.frag");
    if ( shader2 )
    {
        vertCode = readShaderFromFile(":/shaders/shader2.vert");
        fragCode = readShaderFromFile(":/shaders/shader2.frag");
    }
    //std::cout << "shader.vert:\n" << vertCode;
    //std::cout << "shader.frag:\n" << fragCode;
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode.c_str()));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode.c_str()));
    program->addBindAttribLocation("tangent", 6);
    program->addBindAttribLocation("binormal", 7);
    stateSet->setAttributeAndModes(program.get());
    stateSet->addUniform(new osg::Uniform("colorMap", 0));
    stateSet->addUniform(new osg::Uniform("normalMap", 1));
    stateSet->addUniform(new osg::Uniform("roughnessMap", 2));
    stateSet->addUniform(new osg::Uniform("normalMapping", normalMapping));
}

void SceneRoot::createSphere(osg::Vec3 pos, bool normalMapping, bool shader2)
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

    osg::ref_ptr<osg::Texture2D> texture0 = readTextureFromFile("../../../data/DiamondPlate008C_1K_Color.jpg");
    if ( texture0.valid() )
    {
        stateSet->setTextureAttributeAndModes(0, texture0, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Texture2D> texture1 = readTextureFromFile("../../../data/DiamondPlate008C_1K_NormalGL.jpg");
    if ( texture1.valid() )
    {
        stateSet->setTextureAttributeAndModes(1, texture1, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Texture2D> texture2 = readTextureFromFile("../../../data/DiamondPlate008C_1K_Roughness.jpg");
    if ( texture2.valid() )
    {
        stateSet->setTextureAttributeAndModes(2, texture2, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    std::string vertCode = readShaderFromFile(":/shaders/shader.vert");
    std::string fragCode = readShaderFromFile(":/shaders/shader.frag");
    if ( shader2 )
    {
        vertCode = readShaderFromFile(":/shaders/shader2.vert");
        fragCode = readShaderFromFile(":/shaders/shader2.frag");
    }
    //std::cout << "shader.vert:\n" << vertCode;
    //std::cout << "shader.frag:\n" << fragCode;
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode.c_str()));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode.c_str()));
    program->addBindAttribLocation("tangent", 6);
    program->addBindAttribLocation("binormal", 7);
    stateSet->setAttributeAndModes(program.get());
    stateSet->addUniform(new osg::Uniform("colorMap", 0));
    stateSet->addUniform(new osg::Uniform("normalMap", 1));
    stateSet->addUniform(new osg::Uniform("roughnessMap", 2));
    stateSet->addUniform(new osg::Uniform("normalMapping", normalMapping));
}

std::string SceneRoot::readShaderFromFile(const char* path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ts(&file);
    QString code = ts.readAll();
    return code.toStdString();
}

osg::Texture2D* SceneRoot::readTextureFromFile(const char* path)
{
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(path);
    if ( image.valid() )
    {
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
        texture->setImage(image.get());

        texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture::MIRROR);
        texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture::MIRROR);

        texture->setNumMipmapLevels(4);
        texture->setMaxAnisotropy(8.0);

        texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_NEAREST);
        texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);

        return texture.release();
    }
    else
    {
        std::cerr << "Cannot open file: " << path << std::endl;
    }

    return nullptr;
}
