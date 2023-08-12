#include <SceneRoot.h>

#include <osg/AnimationPath>
#include <osg/Geode>
#include <osg/ShapeDrawable>

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

    CreateWall();
    CreateDoor();
    CreateAnimation();
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot() {}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::CreateWall()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild( geode.get() );

    osg::ref_ptr<osg::Box> boxL = new osg::Box( osg::Vec3f(-4.0, 0.0, 0.0), 5.0f, 0.3f, 5.0f );
    osg::ref_ptr<osg::Box> boxR = new osg::Box( osg::Vec3f( 4.0, 0.0, 0.0), 5.0f, 0.3f, 5.0f );

    osg::ref_ptr<osg::ShapeDrawable> shapeL = new osg::ShapeDrawable( boxL.get() );
    osg::ref_ptr<osg::ShapeDrawable> shapeR = new osg::ShapeDrawable( boxR.get() );
    geode->addDrawable( shapeL.get() );
    geode->addDrawable( shapeR.get() );
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::CreateDoor()
{
    mt_ = new osg::MatrixTransform();
    _root->addChild( mt_.get() );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    mt_->addChild( geode.get() );

//    osg::Matrix m = mt_->getMatrix();
//    m.makeTranslate(3.0, 0.0, 0.0);
//    mt_->setMatrix(m);

    osg::ref_ptr<osg::Box> box = new osg::Box( osg::Vec3f(0.0, 0.3, 0.0), 3.0f, 0.3f, 5.0f );

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( box.get() );
    shape->setColor( osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) );
    geode->addDrawable( shape.get() );
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::CreateAnimation()
{
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath();
    //path->setLoopMode( osg::AnimationPath::NO_LOOPING );
    path->setLoopMode( osg::AnimationPath::SWING );

    path->insert(0.0, osg::AnimationPath::ControlPoint(osg::Vec3(0.0, 0.0, 0.0)));
    path->insert(5.0, osg::AnimationPath::ControlPoint(osg::Vec3(3.0, 0.0, 0.0)));

    osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback();

    apcb->setAnimationPath(path.release());
    //apcb->setTimeOffset(-2.5);
    //apcb->setPause(true);

    mt_->setUpdateCallback( apcb.get() );
}
