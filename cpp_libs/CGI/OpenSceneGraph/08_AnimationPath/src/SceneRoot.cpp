#include <SceneRoot.h>

#include <osg/AnimationPath>
#include <osg/Geode>
#include <osg/ShapeDrawable>

#include <osgDB/WriteFile>

#include <AnimationPathCallback.h>

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
    createWall();
    createDoor();
    createAnimation();

    //osgDB::writeNodeFile(*_root, "output.osgt");
}

void SceneRoot::createWall()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild(geode.get());

    osg::ref_ptr<osg::Box> boxL = new osg::Box(osg::Vec3f(-4.0, 0.0, 0.0), 5.0f, 0.3f, 5.0f);
    osg::ref_ptr<osg::Box> boxR = new osg::Box(osg::Vec3f( 4.0, 0.0, 0.0), 5.0f, 0.3f, 5.0f);

    osg::ref_ptr<osg::ShapeDrawable> shapeL = new osg::ShapeDrawable(boxL.get());
    osg::ref_ptr<osg::ShapeDrawable> shapeR = new osg::ShapeDrawable(boxR.get());
    geode->addDrawable(shapeL.get());
    geode->addDrawable(shapeR.get());
}

void SceneRoot::createDoor()
{
    _mt = new osg::MatrixTransform();
    _root->addChild(_mt.get());

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _mt->addChild(geode.get());

//    osg::Matrix m = _mt->getMatrix();
//    m.makeTranslate(3.0, 0.0, 0.0);
//    _mt->setMatrix(m);

    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3f(0.0, 0.3, 0.0), 3.0f, 0.3f, 5.0f);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(box.get());
    shape->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    geode->addDrawable(shape.get());
}

void SceneRoot::createAnimation()
{
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath();
    //path->setLoopMode(osg::AnimationPath::NO_LOOPING);
    path->setLoopMode(osg::AnimationPath::SWING);

    path->insert(0.0, osg::AnimationPath::ControlPoint(osg::Vec3(0.0, 0.0, 0.0)));
    path->insert(5.0, osg::AnimationPath::ControlPoint(osg::Vec3(3.0, 0.0, 0.0)));

    osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback();

    //osg::ref_ptr<AnimationPathCallback> apcb = new AnimationPathCallback();
    //apcb->setValue(2.5);

    apcb->setAnimationPath(path.release());
    _mt->setUpdateCallback( apcb.get() );

    apcb->update(*_mt);
    //apcb->setPause(true);
}
