#include <SceneRoot.h>

#include <iostream>

#include <osgDB/ReadFile>
#include <osgAnimation/BasicAnimationManager>

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

    CreateScene();
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot() {}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::CreateScene()
{
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("../../OpenSceneGraph-Data-3.0.0/bignathan.osg");
    _root->addChild(node.get());

    osgAnimation::BasicAnimationManager* manager =
            dynamic_cast<osgAnimation::BasicAnimationManager*>( node->getUpdateCallback() );

    const osgAnimation::AnimationList& animations = manager->getAnimationList();


    std::string animationName = "Idle_Head_Scratch.02";
    for ( unsigned int i=0; i<animations.size(); ++i )
    {
        const std::string& name = animations[i]->getName();

        if ( name==animationName )
        {
            manager->playAnimation( animations[i].get() );
        }

        std::cout << name << std::endl;
    }
}
