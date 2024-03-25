#include <SceneRoot.h>

#include <iostream>

#include <osg/Geode>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/LineWidth>
#include <osg/ShapeDrawable>

#include <Colors.h>

const float sunRadius = 0.1;

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
    //std::cout << _sunAzim_rad << std::endl;

    osg::Quat q(_sunElev_rad, osg::X_AXIS,
               -_sunAzim_rad, osg::Z_AXIS,  
                0.0, osg::Y_AXIS);
    _patLight->setAttitude(q);

    _skyDome._sunAzim_rad = _sunAzim_rad;
    _skyDome._sunElev_rad = _sunElev_rad;

    _skyDome.update();
}

void SceneRoot::createScene()
{
    createLight();
    createPlane();
    createAxes();

    _root->addChild(_skyDome.getNode());
}

void SceneRoot::createLight()
{
    _patLight = new osg::PositionAttitudeTransform();
    _root->addChild(_patLight.get());

    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
    _patLight->addChild(pat.get());

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();
    pat->addChild(lightSource.get());

    bool drawSun = false;
    if ( drawSun )
    {
        osg::ref_ptr<osg::Geode> geode = new osg::Geode();
        pat->addChild(geode.get());

        osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(osg::Vec3f(), sunRadius);

        osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(sphere.get());
        shape->setColor(osg::Vec4(1.0, 1.0, 0.0, 1.0));
        geode->addDrawable(shape.get());
    }

    osg::ref_ptr<osg::Light> lightSun = new osg::Light();

    lightSun->setLightNum(0);

    osg::Vec4 color(1.0, 1.0, 1.0, 1.0);
    osg::Vec3d position(0.0, 5.0 + sunRadius, 0.0);

    lightSun->setPosition(osg::Vec4d(position, 1.0));
    pat->setPosition(position);

    lightSun->setAmbient  ( color );
    lightSun->setDiffuse  ( color );
    lightSun->setSpecular ( color );

    lightSun->setConstantAttenuation(1.0);

    lightSource->setLight(lightSun.get());

    lightSource->setLocalStateSetModes(osg::StateAttribute::ON);
    lightSource->setStateSetModes(*_root->getOrCreateStateSet(), osg::StateAttribute::ON);
}

void SceneRoot::createPlane()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild(geode.get());

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
    geode->addDrawable( geom.get() );

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();

    const float half_size = 6.0;
    v->push_back(osg::Vec3(-half_size, -half_size, 0.0));
    v->push_back(osg::Vec3( half_size, -half_size, 0.0));
    v->push_back(osg::Vec3( half_size,  half_size, 0.0));
    v->push_back(osg::Vec3(-half_size,  half_size, 0.0));

    n->push_back(osg::Vec3(0.0, 0.0, 1.0));
    c->push_back(osg::Vec4(Colors::green * 0.5, 1.0));

    geom->setVertexArray( v.get() );
    geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::TRIANGLE_FAN, 0, v->size() ) );
    geom->setNormalArray( n.get() );
    geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
    geom->setColorArray( c.get() );
    geom->setColorBinding( osg::Geometry::BIND_OVERALL );
}

void SceneRoot::createAxes()
{
    constexpr double len = 10.0;

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild(geode.get());

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();  // normals
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();  // normals
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();  // colors

    v->push_back(osg::Vec3d(0.0, 0.0, 0.0));
    v->push_back(osg::Vec3d(len, 0.0, 0.0));
    c->push_back(osg::Vec4(Colors::red, 1.0));
    c->push_back(osg::Vec4(Colors::red, 1.0));

    v->push_back(osg::Vec3d(0.0, 0.0, 0.0));
    v->push_back(osg::Vec3d(0.0, len, 0.0));
    c->push_back(osg::Vec4(Colors::lime, 1.0));
    c->push_back(osg::Vec4(Colors::lime, 1.0));

    v->push_back(osg::Vec3d(0.0, 0.0, 0.0));
    v->push_back(osg::Vec3d(0.0, 0.0, len));
    c->push_back(osg::Vec4(Colors::blue, 1.0));
    c->push_back(osg::Vec4(Colors::blue, 1.0));

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
