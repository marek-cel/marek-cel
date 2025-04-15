#include <SceneRoot.h>

#include <osg/Geode>
#include <osg/LightSource>
#include <osg/Material>
#include <osg/ShapeDrawable>

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

    createScene();
}

void SceneRoot::createScene()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild(geode.get());

    createGround();
    createSceneLight();

    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3f(), 10.0, 10.0, 10.0);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(box.get());
    geode->addDrawable(shape.get());
}

void SceneRoot::createGround()
{
    const double w_2 = 50.0;
    const double l_2 = 50.0;

    osg::ref_ptr<osg::Geode> geodeGround = new osg::Geode();
    _root->addChild( geodeGround.get() );

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
    geodeGround->addDrawable( geom.get() );

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();

    v->push_back( osg::Vec3d( -w_2, -l_2, 0.0 ) );
    v->push_back( osg::Vec3d( -w_2,  l_2, 0.0 ) );
    v->push_back( osg::Vec3d(  w_2,  l_2, 0.0 ) );
    v->push_back( osg::Vec3d(  w_2, -l_2, 0.0 ) );

    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec2Array> t = new osg::Vec2Array();
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();

    osg::Vec3d tmp = ( v->at( 1 ) - v->at( 0 ) ) ^ ( v->at( 2 ) - v->at( 0 ) );
    tmp.normalize();
    n->push_back( tmp );

    c->push_back( osg::Vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );

    geom->setVertexArray( v );
    geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::TRIANGLE_FAN, 0, v->size() ) );

    geom->setNormalArray( n.get() );
    geom->setNormalBinding( osg::Geometry::BIND_OVERALL );

    //geom->setColorArray( c.get() );
    //geom->setColorBinding( osg::Geometry::BIND_OVERALL );

    // material
    osg::ref_ptr<osg::Material> material = new osg::Material();
    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    material->setAmbient( osg::Material::FRONT, osg::Vec4f( 0.0f, 0.5f, 0.0f, 1.0f ) );
    material->setDiffuse( osg::Material::FRONT, osg::Vec4f( 0.0f, 0.3f, 0.0f, 1.0f ) );

    geodeGround->getOrCreateStateSet()->setAttribute( material.get() );
}

void SceneRoot::createSceneLight()
{
    osg::ref_ptr<osg::PositionAttitudeTransform> patSun = new osg::PositionAttitudeTransform();
    _root->addChild( patSun.get() );

    patSun->setAttitude( osg::Quat( 0.0, osg::Z_AXIS, 0.0, osg::Y_AXIS, M_PI_4, osg::X_AXIS ) );

    osg::ref_ptr<osg::LightSource> lightSourceSun = new osg::LightSource();
    patSun->addChild( lightSourceSun.get() );

    osg::ref_ptr<osg::Light> lightSun = new osg::Light();

    lightSun->setLightNum( 0 );

    lightSun->setPosition( osg::Vec4d( 1000.0, 1000.0, 1000.0, 0.0 ) );

    osg::Vec4 lightColor( 255.0/255.0, 255.0/255.0, 250.0/255.0, 1.0 );

    lightSun->setAmbient( lightColor * 0.5 );
    lightSun->setDiffuse( lightColor * 0.8 );
    lightSun->setSpecular( lightColor );

    lightSun->setConstantAttenuation( 1.0 );

    lightSourceSun->setLight( lightSun.get() );

    lightSourceSun->setLocalStateSetModes( osg::StateAttribute::ON );
    lightSourceSun->setStateSetModes( *_root->getOrCreateStateSet(), osg::StateAttribute::ON );
}
