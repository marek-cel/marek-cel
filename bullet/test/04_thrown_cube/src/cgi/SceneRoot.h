#ifndef SCENEROOT_H
#define SCENEROOT_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>
#include <osg/PositionAttitudeTransform>

#include <btBulletDynamicsCommon.h>

////////////////////////////////////////////////////////////////////////////////

class SceneRoot
{
public:

    SceneRoot();

    virtual ~SceneRoot();

    inline osg::Node* getNode() { return _root.get(); }

    void update();

private:

    osg::ref_ptr<osg::Group> _root;
    osg::ref_ptr<osg::PositionAttitudeTransform> _pat;

    btDefaultCollisionConfiguration *_collisionConfiguration;
    btCollisionDispatcher *_dispatcher;
    btBroadphaseInterface *_overlappingPairCache;
    btSequentialImpulseConstraintSolver *_solver;
    btDiscreteDynamicsWorld *_dynamicsWorld;

    btCollisionShape *_groundColShape;
    btCollisionShape *_sphareColShape;

    btRigidBody *_bodyGround;
    btRigidBody *_bodySphere;

    void createCube();
    void createGround();
    void createSceneLight();

    void initPhysics();
};

////////////////////////////////////////////////////////////////////////////////

#endif // SCENEROOT_H
