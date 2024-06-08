#include <SceneRoot.h>

#include <iostream>

#include <osg/Geode>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/LineWidth>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>

#include <Colors.h>

SceneRoot::SceneRoot()
{
    _root = new osg::Group();

    osg::ref_ptr<osg::StateSet> stateSet = _root->getOrCreateStateSet();

    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );

    //initSolarSystem();
    //initTwoBodiesSymmetric();
    //initTwoBodiesAsymmetric();
    //initThreeBodiesSymmetric();
    //initThreeBodiesAsymmetric();
    //initThreeBodiesAsymmetric3D();
    initThreeBodiesAsymmetric3DWithPlanet();
    //initThreeBodiesAsymmetric3DWithPlanetStatic();

    createScene();
}

void SceneRoot::update()
{
    for ( int j = 0; j < 365 * 15; j++ )
    {
        for ( int i = 0; i < _n; i++ )
        {
            _bodies[i]->update(j%365);
        }
        for ( int i = 0; i < _n; i++ )
        {
            _bodies[i]->updateFine();
        }
    }
}

void SceneRoot::createScene()
{
    createLight();

    for ( int i = 0; i < _n; i++ )
    {
        _root->addChild(_bodies[i]->getNode());
    }
}

void SceneRoot::createLight()
{
    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
    _root->addChild(pat.get());

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();
    pat->addChild(lightSource.get());

    bool drawSun = false;
    if ( drawSun )
    {
        osg::ref_ptr<osg::Geode> geode = new osg::Geode();
        pat->addChild(geode.get());

        osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(osg::Vec3f(), 1.0);

        osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(sphere.get());
        shape->setColor(osg::Vec4(1.0, 1.0, 0.0, 1.0));
        geode->addDrawable(shape.get());
    }

    osg::ref_ptr<osg::Light> lightSun = new osg::Light();

    lightSun->setLightNum(0);

    osg::Vec3d position(10.0, -10.0, 10.0);

    lightSun->setPosition(osg::Vec4d(position, 1.0));
    pat->setPosition(position);

    lightSun->setAmbient  ( osg::Vec4(0.2, 0.2, 0.2, 1.0) );
    lightSun->setDiffuse  ( osg::Vec4(1.0, 1.0, 1.0, 1.0) );
    lightSun->setSpecular ( osg::Vec4(1.0, 1.0, 1.0, 1.0) );

    lightSun->setConstantAttenuation(1.0);

    lightSource->setLight(lightSun.get());

    lightSource->setLocalStateSetModes(osg::StateAttribute::ON);
    lightSource->setStateSetModes(*_root->getOrCreateStateSet(), osg::StateAttribute::ON);
}

void SceneRoot::initSolarSystem()
{
    _n = 8;

    osg::Vec3 pos[9];
    osg::Vec3 vel[9];

    pos[1] = osg::Vec3(5.2, 0.0, 0.0);
    vel[1] = osg::Vec3(0.0, 0.0, 13.0);

    pos[2] = osg::Vec3(9.6, 0.0, 0.0);
    vel[2] = osg::Vec3(0.0, 0.0, 9.7);

    pos[3] = osg::Vec3(20.0, 0.0, 0.0);
    vel[3] = osg::Vec3(0.0, 0.0, 6.8);

    pos[4] = osg::Vec3(30.0, 0.0, 0.0);
    vel[4] = osg::Vec3(0.0, 0.0, 5.4);

    pos[5] = osg::Vec3(1.0, 0.0, 0.0);
    vel[5] = osg::Vec3(0.0, 0.0, 29.8);

    pos[6] = osg::Vec3(0.7, 0.0, 0.0);
    vel[6] = osg::Vec3(0.0, 0.0, 35.0);

    pos[7] = osg::Vec3(1.5, 0.0, 0.0);
    vel[7] = osg::Vec3(0.0, 0.0, 24.0);

    _bodies[0] = new Body(_bodies, 0, _n, Colors::yellow , 1.0     , pos[0], vel[0] );
    _bodies[1] = new Body(_bodies, 1, _n, Colors::red    , 0.001   , pos[1], vel[1] );
    _bodies[2] = new Body(_bodies, 2, _n, Colors::orange , 0.0003  , pos[2], vel[2] );
    _bodies[3] = new Body(_bodies, 3, _n, Colors::blue   , 0.00004 , pos[3], vel[3] );
    _bodies[4] = new Body(_bodies, 4, _n, Colors::blue   , 5.2e-5  , pos[4], vel[4] );
    _bodies[5] = new Body(_bodies, 5, _n, Colors::green  , 3.0e-6  , pos[5], vel[5] );
    _bodies[6] = new Body(_bodies, 6, _n, Colors::orange , 2.5e-6  , pos[6], vel[6] );
    _bodies[7] = new Body(_bodies, 7, _n, Colors::red    , 3.2e-7  , pos[7], vel[7] );
}

void SceneRoot::initTwoBodiesSymmetric()
{
    _n = 2;

    osg::Vec3 pos[4];
    osg::Vec3 vel[4];

    double r = 20.0;
    double V = 4.0;

    pos[0] = osg::Vec3(-r, 0.0, 0.0);
    vel[0] = osg::Vec3(0.0, 0.0, -V);

    pos[1] = osg::Vec3(r, 0.0, 0.0);
    vel[1] = osg::Vec3(0.0, 0.0, V);

    _bodies[0] = new Body(_bodies, 0, _n, Colors::red   , 1.0, pos[0], vel[0] );
    _bodies[1] = new Body(_bodies, 1, _n, Colors::blue  , 1.0, pos[1], vel[1] );
}

void SceneRoot::initTwoBodiesAsymmetric()
{
    _n = 2;

    osg::Vec3 pos[4];
    osg::Vec3 vel[4];

    double r = 20.0;
    double V = 4.0;

    pos[0] = osg::Vec3(-r/2.0, 0.0, 0.0);
    vel[0] = osg::Vec3(0.0, 0.0, -V/2.0);

    pos[1] = osg::Vec3(r, 0.0, 0.0);
    vel[1] = osg::Vec3(0.0, 0.0, V);

    _bodies[0] = new Body(_bodies, 0, _n, Colors::red   , 1.3, pos[0], vel[0] );
    _bodies[1] = new Body(_bodies, 1, _n, Colors::blue  , 0.7, pos[1], vel[1] );
}

void SceneRoot::initThreeBodiesSymmetric()
{
    _n = 3;

    osg::Vec3 pos[4];
    osg::Vec3 vel[4];

    double r = 20.0;
    double a = 0.0;
    double V = 5.0;
    std::cout << V << std::endl;
    for ( int i = 0; i < _n; i++ )
    {
        double x = sin(a) * r;
        double z = cos(a) * r;
        pos[i] = osg::Vec3(x, 0.0, z);
        double u = -cos(a) * V;
        double v = sin(a) * V;
        vel[i] = osg::Vec3(u, 0.0, v);

        a += 2.0 * M_PI / 3.0;
    }

    _bodies[0] = new Body(_bodies, 0, _n, Colors::red   , 1.0, pos[0], vel[0] );
    _bodies[1] = new Body(_bodies, 1, _n, Colors::green , 1.0, pos[1], vel[1] );
    _bodies[2] = new Body(_bodies, 2, _n, Colors::blue  , 1.0, pos[2], vel[2] );
}


void SceneRoot::initThreeBodiesAsymmetric()
{
    _n = 3;

    osg::Vec3 pos[4];
    osg::Vec3 vel[4];

    double r = 20.0;
    double a = 0.0;
    double V = 5.0;
    std::cout << V << std::endl;
    for ( int i = 0; i < _n; i++ )
    {
        V *= 1.0 + 0.1*i;

        double x = sin(a) * r;
        double z = cos(a) * r;
        pos[i] = osg::Vec3(x, 0.0, z);
        double u = -cos(a) * V;
        double v = sin(a) * V;
        vel[i] = osg::Vec3(u, 0.0, v);

        a += 2.0 * M_PI / 3.0;
    }

    _bodies[0] = new Body(_bodies, 0, _n, Colors::red   , 1.1, pos[0], vel[0] );
    _bodies[1] = new Body(_bodies, 1, _n, Colors::green , 1.0, pos[1], vel[1] );
    _bodies[2] = new Body(_bodies, 2, _n, Colors::blue  , 0.9, pos[2], vel[2] );
}

void SceneRoot::initThreeBodiesAsymmetric3D()
{
    _n = 3;

    osg::Vec3 pos[4];
    osg::Vec3 vel[4];

    double r = 20.0;
    double V = 4.0;

    pos[0] = osg::Vec3(-r, 0.0, 0.0);
    vel[0] = osg::Vec3(0.0, 0.0, -V);

    pos[1] = osg::Vec3(r, 0.0, 0.0);
    vel[1] = osg::Vec3(0.0, 0.0, V);

    pos[2] = osg::Vec3(0.0, r, 0.0);
    vel[2] = osg::Vec3(0.0, 0.0, V);

    _bodies[0] = new Body(_bodies, 0, _n, Colors::red   , 1.1, pos[0], vel[0] );
    _bodies[1] = new Body(_bodies, 1, _n, Colors::green , 1.0, pos[1], vel[1] );
    _bodies[2] = new Body(_bodies, 2, _n, Colors::blue  , 0.9, pos[2], vel[2] );
}

void SceneRoot::initThreeBodiesAsymmetric3DWithPlanet()
{
    _n = 4;

    osg::Vec3 pos[4];
    osg::Vec3 vel[4];

    double r = 30.0;
    double V = 3.0;

    pos[0] = osg::Vec3(-r, 0.0, 0.0);
    vel[0] = osg::Vec3(0.0, 0.0, -V);

    pos[1] = osg::Vec3(r, 0.0, 0.0);
    vel[1] = osg::Vec3(0.0, 0.0, V);

    pos[2] = osg::Vec3(0.0, r, 0.0);
    vel[2] = osg::Vec3(V/2.0, 0.0, 0.0);

    osg::Vec3 norm1 = pos[1];
    norm1.normalize();

    pos[3] = pos[1] * 1.2;
    vel[3] = vel[1] * 0.8;

    _bodies[0] = new Body(_bodies, 0, _n, Colors::red   , 1.2  , pos[0], vel[0] );
    _bodies[1] = new Body(_bodies, 1, _n, Colors::green , 1.0  , pos[1], vel[1] );
    _bodies[2] = new Body(_bodies, 2, _n, Colors::blue  , 0.8  , pos[2], vel[2] );
    _bodies[3] = new Body(_bodies, 3, _n, Colors::grey  , 3.0e-6 , pos[3], vel[3] );

    // pos[3] = pos[1] - osg::Vec3(5.0, -5.0, 0.0);
    // vel[3] = vel[1] + osg::Vec3(9.0,  0.0, 0.0);;

    // _bodies[0] = new Body(_bodies, 0, _n, Colors::red   , 1.8  , pos[0], vel[0] );
    // _bodies[1] = new Body(_bodies, 1, _n, Colors::green , 0.9  , pos[1], vel[1] );
    // _bodies[2] = new Body(_bodies, 2, _n, Colors::blue  , 0.4  , pos[2], vel[2] );
    // _bodies[3] = new Body(_bodies, 3, _n, Colors::grey  , 3.0e-6 , pos[3], vel[3] );
}

void SceneRoot::initThreeBodiesAsymmetric3DWithPlanetStatic()
{
    _n = 4;

    osg::Vec3 pos[4];
    osg::Vec3 vel[4];

    double r = 30.0;
    double V = 3.0;

    pos[0] = osg::Vec3(-r, 0.0, 0.0);
    vel[0] = osg::Vec3(0.0, 0.0, V);

    pos[1] = osg::Vec3(r, 0.0, 0.0);
    vel[1] = osg::Vec3(0.0, 0.0, -V);

    pos[2] = osg::Vec3(0.0, 0.0, 2.0*r);
    vel[2] = osg::Vec3(0.5*V, 0.0, 0.0);

    osg::Vec3 norm1 = pos[1];
    norm1.normalize();

    pos[3] = pos[1] + osg::Vec3(.0,  8.0,  0.0);
    vel[3] = vel[1] + osg::Vec3(.0,  0.0,  2.0);

    _bodies[0] = new Body(_bodies, 0, _n, Colors::red   , 1.2  , pos[0], vel[0] );
    _bodies[1] = new Body(_bodies, 1, _n, Colors::green , 1.0  , pos[1], vel[1] );
    _bodies[2] = new Body(_bodies, 2, _n, Colors::blue  , 0.8  , pos[2], vel[2] );
    _bodies[3] = new Body(_bodies, 3, _n, Colors::grey  , 3.0e-6 , pos[3], vel[3] );
}