#include <SceneRoot.h>

#include <osg/Light>
#include <osg/LightSource>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>

SceneRoot::SceneRoot()
{
    _root = new osg::Group();

    osg::ref_ptr<osg::StateSet> stateSet = _root->getOrCreateStateSet();

    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT1         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT2         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );

    createScene();
}

void SceneRoot::createScene()
{
    osg::ref_ptr<osg::PositionAttitudeTransform> patMain = new osg::PositionAttitudeTransform();
    _root->addChild( patMain.get() );

    patMain->setPosition( osg::Vec3d( 100.0, 0.0, 0.0 ) );

    osg::ref_ptr<osg::Node> glider = osgDB::readNodeFile( "../../../OpenSceneGraph-Data-3.0.0/cessna.osgt" );

    if ( glider.valid() )
    {
        _root->addChild( glider.get() );
        patMain->addChild( glider.get() );
    }

    for ( int i = 0; i < 2; i++ )
    {
        osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
        patMain->addChild( pat.get() );

        osg::ref_ptr<osg::Light> light = new osg::Light();
        osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();

        light->setLightNum( i + 1 );

        osg::Vec4 color( 1.0f, 0.0f, 0.0f, 1.0f );
        osg::Vec3d position( 10.0f, 0.0f, 0.0f );

        if ( i % 2 == 0 )
        {
            color = osg::Vec4( 0.0f, 1.0f, 0.0f, 1.0f );
            position = osg::Vec3d( -10.0, 0.0, 0.0 );
        }

        pat->setPosition( position );

        //light->setPosition( osg::Vec4d( position, 1.0 ) );
        light->setPosition( osg::Vec4( 0.0, 0.0, 0.0, 1.0 ) );
        light->setDiffuse( color );

        light->setConstantAttenuation(1.0f);
        light->setLinearAttenuation(0.2f);
        light->setQuadraticAttenuation(0.02f);

        lightSource->setLight( light.get() );
        //lightSource->setLocalStateSetModes( osg::StateAttribute::ON );
        //lightSource->setStateSetModes( *m_switch->getOrCreateStateSet(), osg::StateAttribute::ON );
        lightSource->setReferenceFrame( osg::LightSource::RELATIVE_RF );

        pat->addChild( lightSource.get() );
    }
}
