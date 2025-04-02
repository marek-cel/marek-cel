#include <SceneRoot.h>

#include <iostream>

#include <osg/LineWidth>
#include <osg/Geometry>

#include <osgAnimation/Skeleton>
#include <osgAnimation/UpdateBone>
#include <osgAnimation/StackedTranslateElement>
#include <osgAnimation/StackedQuaternionElement>

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
    osg::ref_ptr<osgAnimation::Skeleton> skelroot = new osgAnimation::Skeleton;
    skelroot->setDefaultUpdateCallback();
    _root->addChild(skelroot.get());

//    osg::ref_ptr<osg::Geode> geodeXp = createBoneShape(osg::Vec3d(0.0, 0.0, 0.0), osg::Vec3d(1.0, 0.0, 0.0));
//    osg::ref_ptr<osg::Geode> geodeXn = createBoneShape(osg::Vec3d(0.0, 0.0, 0.0), osg::Vec3d(-1.0, 0.0, 0.0));

//    osg::ref_ptr<osg::Geode> geodeYp = createBoneShape(osg::Vec3d(0.0, 0.0, 0.0), osg::Vec3d(0.0, 1.0, 0.0));
//    osg::ref_ptr<osg::Geode> geodeYn = createBoneShape(osg::Vec3d(0.0, 0.0, 0.0), osg::Vec3d(0.0, -1.0, 0.0));

//    osg::ref_ptr<osg::Geode> geodeZp = createBoneShape(osg::Vec3d(0.0, 0.0, 0.0), osg::Vec3d(0.0, 0.0, 1.0));
//    osg::ref_ptr<osg::Geode> geodeZn = createBoneShape(osg::Vec3d(0.0, 0.0, 0.0), osg::Vec3d(0.0, 0.0, -1.0));

//    _root->addChild(geodeXp.get());
//    _root->addChild(geodeXn.get());
//    _root->addChild(geodeYp.get());
//    _root->addChild(geodeYn.get());
//    _root->addChild(geodeZp.get());
//    _root->addChild(geodeZn.get());

    osgAnimation::Bone* bone0  = createBone("bone0"  , osg::Vec3(0.0, 0.0, 0.0), skelroot.get());

    osgAnimation::Bone* bone11 = createBone("bone11" , osg::Vec3(0.5, 0.0, 0.0), bone0);

    osgAnimation::Bone* bone12 = createEndBone("bone12", osg::Vec3(1.0,  0.0, 0.0), bone11);

    osg::ref_ptr<osgAnimation::Animation> anim = new osgAnimation::Animation;
    anim->setPlayMode(osgAnimation::Animation::PPONG);
    anim->addChannel(createChannel("bone11", osg::Y_AXIS, osg::PI_4));
    anim->addChannel(createChannel("bone12", osg::Y_AXIS, osg::PI_2));

    osg::ref_ptr<osgAnimation::BasicAnimationManager> manager = new osgAnimation::BasicAnimationManager();
    manager->registerAnimation(anim.get());
    manager->playAnimation(anim.get());

    _root->setUpdateCallback(manager.get());
}

osgAnimation::Bone* SceneRoot::createBone(const char* name, const osg::Vec3& trans, osg::Group* parent)
{
    osg::ref_ptr<osgAnimation::Bone> bone = new osgAnimation::Bone();
    parent->insertChild(0, bone.get());
    parent->addChild(createBoneShape(osg::Vec3d(), trans));

    osg::ref_ptr<osgAnimation::UpdateBone> updater = new osgAnimation::UpdateBone(name);
    updater->getStackedTransforms().push_back(new osgAnimation::StackedTranslateElement("translate", trans));
    updater->getStackedTransforms().push_back(new osgAnimation::StackedQuaternionElement("quaternion"));
    bone->setUpdateCallback( updater.get() );

    bone->setMatrixInSkeletonSpace(osg::Matrix::translate(trans) * bone->getMatrixInSkeletonSpace());
    bone->setName( name );

    return bone.get();
}

osgAnimation::Bone* SceneRoot::createEndBone(const char* name, const osg::Vec3& trans, osg::Group* parent)
{
    osgAnimation::Bone* bone = createBone(name, trans, parent);
    bone->addChild(createBoneShape(osg::Vec3d(), trans));
    return bone;
}

osgAnimation::Channel* SceneRoot::createChannel(const char* name, const osg::Vec3& axis, float rad)
{
    osg::ref_ptr<osgAnimation::QuatSphericalLinearChannel> ch = new osgAnimation::QuatSphericalLinearChannel();
    ch->setName("quaternion");
    ch->setTargetName(name);

    osgAnimation::QuatKeyframeContainer* kfs = ch->getOrCreateSampler()->getOrCreateKeyframeContainer();
    kfs->push_back( osgAnimation::QuatKeyframe(0.0, osg::Quat(0.0, axis)));
    kfs->push_back( osgAnimation::QuatKeyframe(8.0, osg::Quat(rad, axis)));
    return ch.release();
}

osg::Geode* SceneRoot::createBoneShape(osg::Vec3d vb, osg::Vec3d ve)
{
    double length = (ve - vb).length();
    osg::Vec3d v_tang = (ve - vb) / length;
    osg::Vec3d v_norm = getOrthogonal(v_tang);
    osg::Vec3d v_bnrm = v_tang ^ v_norm;
    v_norm.normalize();
    v_bnrm.normalize();

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();

    n->push_back(osg::Vec3(0.0, 0.0, 1.0));
    c->push_back(osg::Vec4(1.0, 0.0, 1.0, 1.0));

    v->push_back(vb);
    v->push_back(vb + v_tang * 0.2 * length + v_norm * 0.1 * length + v_bnrm * 0.1 * length);
    v->push_back(vb);
    v->push_back(vb + v_tang * 0.2 * length - v_norm * 0.1 * length + v_bnrm * 0.1 * length);
    v->push_back(vb);
    v->push_back(vb + v_tang * 0.2 * length + v_norm * 0.1 * length - v_bnrm * 0.1 * length);
    v->push_back(vb);
    v->push_back(vb + v_tang * 0.2 * length - v_norm * 0.1 * length - v_bnrm * 0.1 * length);

    v->push_back(vb + v_tang * 0.2 * length + v_norm * 0.1 * length - v_bnrm * 0.1 * length);
    v->push_back(vb + v_tang * 0.2 * length - v_norm * 0.1 * length - v_bnrm * 0.1 * length);
    v->push_back(vb + v_tang * 0.2 * length - v_norm * 0.1 * length - v_bnrm * 0.1 * length);
    v->push_back(vb + v_tang * 0.2 * length - v_norm * 0.1 * length + v_bnrm * 0.1 * length);
    v->push_back(vb + v_tang * 0.2 * length - v_norm * 0.1 * length + v_bnrm * 0.1 * length);
    v->push_back(vb + v_tang * 0.2 * length + v_norm * 0.1 * length + v_bnrm * 0.1 * length);
    v->push_back(vb + v_tang * 0.2 * length + v_norm * 0.1 * length + v_bnrm * 0.1 * length);
    v->push_back(vb + v_tang * 0.2 * length + v_norm * 0.1 * length - v_bnrm * 0.1 * length);

    v->push_back(vb + v_tang * length);
    v->push_back(vb + v_tang * 0.2 * length + v_norm * 0.1 * length + v_bnrm * 0.1 * length);
    v->push_back(vb + v_tang * length);
    v->push_back(vb + v_tang * 0.2 * length - v_norm * 0.1 * length + v_bnrm * 0.1 * length);
    v->push_back(vb + v_tang * length);
    v->push_back(vb + v_tang * 0.2 * length + v_norm * 0.1 * length - v_bnrm * 0.1 * length);
    v->push_back(vb + v_tang * length);
    v->push_back(vb + v_tang * 0.2 * length - v_norm * 0.1 * length - v_bnrm * 0.1 * length);


    geom->setVertexArray(v.get());
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size()));

    geom->setNormalArray(n.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geom->setColorArray(c.get());
    geom->setColorBinding(osg::Geometry::BIND_OVERALL);

    geode->addDrawable(geom.get());

    osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth();
    lineWidth->setWidth(2.0);

    osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();
    stateSet->setAttributeAndModes(lineWidth, osg::StateAttribute::ON);
    stateSet->setMode(GL_LIGHTING   , osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
    stateSet->setMode(GL_DEPTH_TEST , osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
    stateSet->setRenderBinDetails(99, "DepthSortedBin");

    return geode.release();
}

osg::Vec3d SceneRoot::getOrthogonal(osg::Vec3d v)
{
    osg::ref_ptr<osg::Vec3Array> e = new osg::Vec3Array();
    e->push_back(osg::Vec3d(1.0, 0.0, 0.0));
    e->push_back(osg::Vec3d(0.0, 1.0, 0.0));
    e->push_back(osg::Vec3d(0.0, 0.0, 1.0));

    double d[3];

    d[0] = v * e->at(0);
    d[1] = v * e->at(1);
    d[2] = v * e->at(2);

    int i_min = 0;
    for ( int i = 0; i < 3; ++i )
    {
        if ( fabs(d[i]) < fabs(d[i_min]) ) i_min = i;
    }

    return v ^ e->at(i_min);
}

osg::Vec3d SceneRoot::getNormal(osg::Vec3d v0, osg::Vec3d v1, osg::Vec3d v2)
{
    osg::Vec3d vn = (v1 - v0) ^ (v2 - v0);
    vn.normalize();
    return vn;
}
