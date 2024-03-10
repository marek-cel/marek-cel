#include <osgDB/ReadFile>

#include <SceneRoot.h>

////////////////////////////////////////////////////////////////////////////////

SceneRoot::SceneRoot()
{
    m_root = new osg::Group();

    osg::ref_ptr<osg::StateSet> stateSet = m_root->getOrCreateStateSet();

    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );

    osg::ref_ptr<osg::Node> glider = osgDB::readNodeFile( "../../OpenSceneGraph-Data-3.0.0/glider.osgt" );

    if ( glider.valid() )
    {
        m_root->addChild( glider.get() );
    }
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot() {}
