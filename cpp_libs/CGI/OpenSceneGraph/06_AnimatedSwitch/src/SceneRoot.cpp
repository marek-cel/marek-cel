#include <SceneRoot.h>

#include <osg/Switch>
#include <osgDB/ReadFile>

#include <SwitchingCallback.h>

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
    osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("../../OpenSceneGraph-Data-3.0.0/cessna.osg");
    osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("../../OpenSceneGraph-Data-3.0.0/cessnafire.osg");

    _switch = new osg::Switch();
    _root->addChild(_switch.get());
    _switch->addChild( model1.get(), false );
    _switch->addChild( model2.get(), true );

    _switch->setUpdateCallback( new SwitchingCallback );
}
