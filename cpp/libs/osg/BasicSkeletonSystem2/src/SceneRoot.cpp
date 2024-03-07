#include <SceneRoot.h>

#include <osg/LineWidth>
#include <osg/Geometry>


#include <osgAnimation/Skeleton>
#include <osgAnimation/UpdateBone>
#include <osgAnimation/StackedTranslateElement>
#include <osgAnimation/StackedQuaternionElement>

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
    osg::Vec3d vb(0.0, 0.0, 0.0);
    osg::Vec3d ve(0.0, 0.0, 1.0);
    osg::ref_ptr<osg::Geode> geode = createBoneShape(vb, ve);
    _root->addChild(geode.get());
}

////////////////////////////////////////////////////////////////////////////////

osg::Geode* SceneRoot::createBoneShape(osg::Vec3d vb, osg::Vec3d ve)
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    return geode.release();
}
