#include <SceneRoot.h>

#include <iostream>

#include <osg/Geode>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/LineWidth>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

#include <osgDB/ReadFile>

#include <QFile>
#include <QTextStream>

float deg2rad(float deg)
{
    return M_PI * deg / 180.0;
}

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

void SceneRoot::update()
{
    // TODO
}

void SceneRoot::createScene()
{
    createLight();
    createTerrain(osg::Vec3(157.97,-21.48,0.0));
    createAxes();
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
    osg::Vec3d position(2.0, -2.0, 2.0);

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

void SceneRoot::createTerrain(osg::Vec3 pos)
{
    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
    _root->addChild(pat.get());

    pat->setPosition(pos);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    pat->addChild(geode.get());

    osg::ref_ptr<osg::Node> terrain = osgDB::readNodeFile("../../../data/terrain/terrain.osgb");

    if ( !terrain.valid() )
    {
        std::cerr << "Cannot open terrain file." << std::endl;
        return;
    }
    else
    {
        std::cerr << "xxx" << std::endl;
    }

    pat->addChild(terrain.get());

    osg::ref_ptr<osg::StateSet> stateSet = terrain->getOrCreateStateSet();

    std::string vertCode = readShaderFromFile(":/shaders/shader.vert");
    std::string fragCode = readShaderFromFile(":/shaders/shader.frag");
    //std::cout << "shader.vert:\n" << vertCode;
    //std::cout << "shader.frag:\n" << fragCode;
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode.c_str()));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode.c_str()));
    stateSet->setAttributeAndModes(program.get());
}

void SceneRoot::createAxes()
{
    constexpr double len = 1.0;

    osg::Vec3 red(1,0,0);
    osg::Vec3 lime(0,1,0);
    osg::Vec3 blue(0,0,1);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _center->addChild(geode.get());

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();  // normals
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();  // normals
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();  // colors

    v->push_back(osg::Vec3d(0.0, 0.0, 0.0));
    v->push_back(osg::Vec3d(len, 0.0, 0.0));
    c->push_back(osg::Vec4(red, 1.0));
    c->push_back(osg::Vec4(red, 1.0));

    v->push_back(osg::Vec3d(0.0, 0.0, 0.0));
    v->push_back(osg::Vec3d(0.0, len, 0.0));
    c->push_back(osg::Vec4(lime, 1.0));
    c->push_back(osg::Vec4(lime, 1.0));

    v->push_back(osg::Vec3d(0.0, 0.0, 0.0));
    v->push_back(osg::Vec3d(0.0, 0.0, len));
    c->push_back(osg::Vec4(blue, 1.0));
    c->push_back(osg::Vec4(blue, 1.0));

    n->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

    geometry->setVertexArray(v.get());
    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size()));
    geometry->setNormalArray(n.get());
    geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geometry->setColorArray(c.get());
    geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    geode->addDrawable(geometry.get());

    osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth();
    lineWidth->setWidth(2.0f);

    geode->getOrCreateStateSet()->setAttributeAndModes(lineWidth, osg::StateAttribute::ON);
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
