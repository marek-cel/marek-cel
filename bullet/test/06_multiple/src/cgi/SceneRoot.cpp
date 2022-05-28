#include <cgi/SceneRoot.h>

#include <cmath>

#include <osg/Geode>
#include <osg/LightSource>
#include <osg/Material>
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

    initPhysics();

    createBalls();
    createGround();
    createSceneLight();
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot()
{
    for (int i = _dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
    {
        btCollisionObject* obj = _dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState())
        {
            delete body->getMotionState();
        }
        _dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    if ( _groundColShape ) { delete _groundColShape; } _groundColShape = nullptr;

    for ( int i = 0; i < collisionShapes.size(); i++ )
    {
        delete collisionShapes[i];
    }
    collisionShapes.clear();

    if ( _dynamicsWorld ) { delete _dynamicsWorld; } _dynamicsWorld = nullptr;
    if ( _dynamicsWorld ) { delete _dynamicsWorld; } _dynamicsWorld = nullptr;
    if ( _dynamicsWorld ) { delete _dynamicsWorld; } _dynamicsWorld = nullptr;
    if ( _dynamicsWorld ) { delete _dynamicsWorld; } _dynamicsWorld = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::update()
{
    _dynamicsWorld->stepSimulation(1.f / 100.f, 10);

    //print positions of all objects
//    for (int j = _dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
//    {
//        btCollisionObject* obj = _dynamicsWorld->getCollisionObjectArray()[j];
//        btRigidBody* body = btRigidBody::upcast(obj);
//        btTransform trans;
//        if (body && body->getMotionState())
//        {
//            body->getMotionState()->getWorldTransform(trans);
//        }
//        else
//        {
//            trans = obj->getWorldTransform();
//        }
//        printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
//    }

    for ( int i = 0; i < _bodies.size(); i++ )
    {
        double cx = 0.5;
        double s = M_PI * pow( 0.1, 2.0 );
        double rho = 1.225;

        btVector3 drag;
        drag.setX( -0.5 * _bodies[i]->getLinearVelocity().getX() * fabs(_bodies[i]->getLinearVelocity().getZ()) * rho * s * cx );
        drag.setY( -0.5 * _bodies[i]->getLinearVelocity().getY() * fabs(_bodies[i]->getLinearVelocity().getZ()) * rho * s * cx );
        drag.setZ( -0.5 * _bodies[i]->getLinearVelocity().getZ() * fabs(_bodies[i]->getLinearVelocity().getZ()) * rho * s * cx );

        _bodies[i]->applyCentralForce( drag );

        btTransform trans;
        _bodies[i]->getMotionState()->getWorldTransform(trans);
        osg::Vec3d v( trans.getOrigin().getX(),
                      trans.getOrigin().getY(),
                      trans.getOrigin().getZ() );
        _pats[i]->setPosition( v );
    }
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createBalls()
{
    const double h0 = 10.0;
    const double r = 0.1;
    const double d = 2.0 * r;

    const int i_max = floor( 1.0 / d );

    for ( int ix = -i_max; ix <= i_max; ix++ )
    {
        for ( int iy = -i_max; iy <= i_max; iy++ )
        {
            for ( int iz = -i_max; iz <= i_max; iz++ )
            {
                osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
                _root->addChild( pat.get() );
                _pats.push_back( pat );

                osg::ref_ptr<osg::Geode> geode = new osg::Geode();
                pat->addChild( geode.get() );

                osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere( osg::Vec3f( 0.0f, 0.0f, 0.0f ), r );

                osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( sphere.get() );
                geode->addDrawable( shape.get() );

                pat->setPosition( osg::Vec3d( ix * d, iy * d, iz * d ) );

                // bullet
                btSphereShape *sphareColShape = new btSphereShape(btScalar(r));
                collisionShapes.push_back(sphareColShape);

                /// Create Dynamic Objects
                btTransform startTransform;
                startTransform.setIdentity();

                btScalar mass(1.f);

                //rigidbody is dynamic if and only if mass is non zero, otherwise static
                bool isDynamic = (mass != 0.f);

                btVector3 localInertia(0, 0, 0);
                if (isDynamic)
                    sphareColShape->calculateLocalInertia(mass, localInertia);

                startTransform.setOrigin(btVector3(ix * d, iy * d, iz * d + h0));

                //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
                btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
                btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, sphareColShape, localInertia);
                rbInfo.m_restitution     = 0.7f;
                rbInfo.m_friction        = 0.3f;
                rbInfo.m_rollingFriction = 0.1f;
                btRigidBody *bodySphere = new btRigidBody(rbInfo);
                _bodies.push_back(bodySphere);

                _dynamicsWorld->addRigidBody(bodySphere);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createGround()
{
    const double w_2 = 10.0;
    const double l_2 = 10.0;

    osg::ref_ptr<osg::Geode> geodeGround = new osg::Geode();
    _root->addChild( geodeGround.get() );

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
    geodeGround->addDrawable( geom.get() );

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();

    v->push_back( osg::Vec3d( -w_2, -l_2, 0.0 ) );
    v->push_back( osg::Vec3d( -w_2,  l_2, 0.0 ) );
    v->push_back( osg::Vec3d(  w_2,  l_2, 0.0 ) );
    v->push_back( osg::Vec3d(  w_2, -l_2, 0.0 ) );

    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec2Array> t = new osg::Vec2Array();
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();

    osg::Vec3d tmp = ( v->at( 1 ) - v->at( 0 ) ) ^ ( v->at( 2 ) - v->at( 0 ) );
    tmp.normalize();
    n->push_back( tmp );

    c->push_back( osg::Vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );

    geom->setVertexArray( v );
    geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::TRIANGLE_FAN, 0, v->size() ) );

    geom->setNormalArray( n.get() );
    geom->setNormalBinding( osg::Geometry::BIND_OVERALL );

    //geom->setColorArray( c.get() );
    //geom->setColorBinding( osg::Geometry::BIND_OVERALL );

    // material
    osg::ref_ptr<osg::Material> material = new osg::Material();
    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    material->setAmbient( osg::Material::FRONT, osg::Vec4f( 0.0f, 0.5f, 0.0f, 1.0f ) );
    material->setDiffuse( osg::Material::FRONT, osg::Vec4f( 0.0f, 0.3f, 0.0f, 1.0f ) );

    geodeGround->getOrCreateStateSet()->setAttribute( material.get() );

    // bullet

    _groundColShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, 0, -50));

    btScalar mass(0.);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        _groundColShape->calculateLocalInertia(mass, localInertia);

    //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, _groundColShape, localInertia);
    rbInfo.m_restitution     = 0.7f;
    rbInfo.m_friction        = 0.5f;
    rbInfo.m_rollingFriction = 0.1f;
    _bodyGround = new btRigidBody(rbInfo);

    //add the body to the dynamics world
    _dynamicsWorld->addRigidBody(_bodyGround);
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createSceneLight()
{
    osg::ref_ptr<osg::PositionAttitudeTransform> patSun = new osg::PositionAttitudeTransform();
    _root->addChild( patSun.get() );

    patSun->setAttitude( osg::Quat( 0.0, osg::Z_AXIS, 0.0, osg::Y_AXIS, M_PI_4, osg::X_AXIS ) );

    osg::ref_ptr<osg::LightSource> lightSourceSun = new osg::LightSource();
    patSun->addChild( lightSourceSun.get() );

    osg::ref_ptr<osg::Light> lightSun = new osg::Light();

    lightSun->setLightNum( 0 );

    lightSun->setPosition( osg::Vec4d( 1000.0, 1000.0, 1000.0, 0.0 ) );

    osg::Vec4 lightColor( 255.0/255.0, 255.0/255.0, 250.0/255.0, 1.0 );

    lightSun->setAmbient( lightColor * 0.5 );
    lightSun->setDiffuse( lightColor * 0.8 );
    lightSun->setSpecular( lightColor );

    lightSun->setConstantAttenuation( 1.0 );

    lightSourceSun->setLight( lightSun.get() );

    lightSourceSun->setLocalStateSetModes( osg::StateAttribute::ON );
    lightSourceSun->setStateSetModes( *_root->getOrCreateStateSet(), osg::StateAttribute::ON );
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::initPhysics()
{
    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    _collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    _dispatcher = new btCollisionDispatcher(_collisionConfiguration);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    _overlappingPairCache = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    _solver = new btSequentialImpulseConstraintSolver;

    _dynamicsWorld = new btDiscreteDynamicsWorld(_dispatcher, _overlappingPairCache, _solver, _collisionConfiguration);

    _dynamicsWorld->setGravity(btVector3(0, 0, -10));
}

