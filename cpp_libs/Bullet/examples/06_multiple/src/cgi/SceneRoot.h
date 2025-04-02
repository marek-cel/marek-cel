#ifndef SCENEROOT_H
#define SCENEROOT_H

////////////////////////////////////////////////////////////////////////////////

#include <vector>

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
    std::vector< osg::ref_ptr<osg::PositionAttitudeTransform> > _pats;

    btDefaultCollisionConfiguration *_collisionConfiguration;
    btCollisionDispatcher *_dispatcher;
    btBroadphaseInterface *_overlappingPairCache;
    btSequentialImpulseConstraintSolver *_solver;
    btDiscreteDynamicsWorld *_dynamicsWorld;

    btCollisionShape *_groundColShape;
    std::vector<btCollisionShape*> collisionShapes;

    btRigidBody *_bodyGround;
    std::vector<btRigidBody*> _bodies;

    void createBalls();
    void createGround();
    void createSceneLight();

    void initPhysics();
};

////////////////////////////////////////////////////////////////////////////////

#endif // SCENEROOT_H
