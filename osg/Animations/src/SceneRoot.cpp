#include <SceneRoot.h>

#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>

#include <FindNode.h>

////////////////////////////////////////////////////////////////////////////////

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

    osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile( "../../00_data_new/tank.osgb" );

    _root->addChild( loadedModel.get() );

    FindNode find( "TurretPAT" );
    find.apply( *(loadedModel.get()) );

    osg::ref_ptr<osg::PositionAttitudeTransform> turretPAT = dynamic_cast<osg::PositionAttitudeTransform*>( find.getFirst().get() );

    turretPAT->setAttitude( osg::Quat( M_PI_4, osg::Z_AXIS ) );
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot() {}
