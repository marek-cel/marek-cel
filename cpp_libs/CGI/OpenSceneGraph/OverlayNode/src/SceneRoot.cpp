#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#include <osg/TexEnv>

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
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );

    create();
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot() {}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::create()
{
    m_pat = new osg::PositionAttitudeTransform();
    m_root->addChild( m_pat.get() );

    m_pat->setAttitude( osg::Quat( -M_PI_2, osg::X_AXIS ) );

    osgSim::OverlayNode::OverlayTechnique technique = osgSim::OverlayNode::OBJECT_DEPENDENT_WITH_ORTHOGRAPHIC_OVERLAY;

    m_overleyNode = new osgSim::OverlayNode( technique );
    m_pat->addChild( m_overleyNode.get() );

    m_overleyNode->getOrCreateStateSet()->setTextureAttribute( 1, new osg::TexEnv( osg::TexEnv::DECAL ) );
//    m_overleyNode->setOverlaySubgraph( shapefile.get() );
    m_overleyNode->setOverlayTextureSizeHint( 1024 );

    m_overleyNode->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
    m_overleyNode->getOrCreateStateSet()->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

    createEarth();
    createBox();
    createSquare();
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createEarth()
{
    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
    m_overleyNode->addChild( pat.get() );

    pat->setAttitude( osg::Quat( M_PI_2, osg::X_AXIS ) );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    pat->addChild( geode.get() );

    osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere( osg::Vec3f(), 100.0f );

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( sphere.get() );
    geode->addDrawable( shape.get() );

    osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile( "../../Data/land_shallow_topo_1024.jpg" );

    if ( image.valid() )
    {
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();

        texture->setImage( image.get() );

        stateSet->setTextureAttributeAndModes( 0, texture.get(), osg::StateAttribute::ON );

        stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
        stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    }
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createBox()
{
    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
    m_pat->addChild( pat.get() );

    pat->setPosition( osg::Vec3( 0.0, 0.0, 120.0 ) );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
//    m_overleyNode->setOverlaySubgraph( geode.get() );
    pat->addChild( geode.get() );

    osg::ref_ptr<osg::Box> box = new osg::Box( osg::Vec3f(), 10.0f, 10.0f, 10.0f );

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( box.get() );
    geode->addDrawable( shape.get() );
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createSquare()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    m_overleyNode->setOverlaySubgraph( geode.get() );

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
    geode->addDrawable( geom.get() );

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
    osg::ref_ptr<osg::Vec2Array> t = new osg::Vec2Array();
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();

    const double a_2 = 5.0;

    v->push_back( osg::Vec3d( -a_2, -a_2, 0.0 ) );
    v->push_back( osg::Vec3d(  a_2, -a_2, 0.0 ) );
    v->push_back( osg::Vec3d(  a_2,  a_2, 0.0 ) );
    v->push_back( osg::Vec3d( -a_2,  a_2, 0.0 ) );

    c->push_back( osg::Vec4( 0.8, 0.8, 0.8, 1.0 ) );
    c->push_back( osg::Vec4( 0.8, 0.8, 0.8, 1.0 ) );
    c->push_back( osg::Vec4( 0.8, 0.8, 0.8, 1.0 ) );
    c->push_back( osg::Vec4( 0.8, 0.8, 0.8, 1.0 ) );

    t->push_back( osg::Vec2( 0, 0 ) );
    t->push_back( osg::Vec2( 1, 0 ) );
    t->push_back( osg::Vec2( 1, 1 ) );
    t->push_back( osg::Vec2( 0, 1 ) );

    n->push_back( osg::Vec3d( 0.0, 0.0, 1.0 ) );

    geom->setNormalArray( n.get() );
    geom->setNormalBinding( osg::Geometry::BIND_OVERALL );

    geom->setColorArray( c.get() );
    geom->setColorBinding( osg::Geometry::BIND_PER_VERTEX );

    geom->setVertexArray( v.get() );
    geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, v->size() ) );

    geom->setTexCoordArray( 0, t.get() );

    osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile( "../00_data/shadow.jpg" );

    if ( image.valid() )
    {
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();

        texture->setImage( image.get() );

        stateSet->setTextureAttributeAndModes( 0, texture.get(), osg::StateAttribute::ON );

        stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
        stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    }
    else
    {
        std::cerr << "xxx" << std::endl;
    }
}
