#include <SceneRoot.h>

#include <osg/AlphaFunc>
#include <osg/BlendFunc>
#include <osg/Billboard>
#include <osg/Depth>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>

#include <osgDB/ReadFile>

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

    stateSet->setMode( GL_CULL_FACE      , osg::StateAttribute::OFF );

    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setAmbient( osg::Material::FRONT_AND_BACK, osg::Vec4(1.0f, 1.0f, 1.0f, 0.5f) );
    material->setDiffuse( osg::Material::FRONT_AND_BACK, osg::Vec4(1.0f, 1.0f, 1.0f, 0.5f) );

    //stateSet->setAttributeAndModes( material.get(), osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE );

    osg::ref_ptr<osg::AlphaFunc> alphaFunc = new osg::AlphaFunc();
    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();
    blendFunc->setFunction( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    alphaFunc->setFunction( osg::AlphaFunc::GEQUAL, 0.05 );
    stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    stateSet->setAttributeAndModes( blendFunc.get(), osg::StateAttribute::ON );
    stateSet->setAttributeAndModes( alphaFunc.get(), osg::StateAttribute::ON );
    stateSet->setMode( GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE );
    stateSet->setRenderBinDetails( 3, "DepthSortedBin" );

    osg::ref_ptr<osg::Depth> depth = new osg::Depth;
    depth->setWriteMask( false );
    stateSet->setAttributeAndModes( depth.get(), osg::StateAttribute::ON );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild( geode.get() );

    osg::ref_ptr<osg::ShapeDrawable> shape1 = new osg::ShapeDrawable();
    shape1->setShape( new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f) );
    geode->addDrawable( shape1.get() );

    osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile( "../00_data/cessna.osgt" );
    //_root->addChild( loadedModel.get() );

    //createBlock( _root.get() );
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot() {}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createBlock( osg::Group *parent )
{
    for ( int i = 0; i < 5; i++ )
    {
        osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
        parent->addChild( pat.get() );

        createSprite( pat.get() );

        double scale = 100.0 * i;

        osg::Vec3 pos( 100.0 * i, 100.0 * i, 0.0 );

        pat->setScale( osg::Vec3( scale, scale, scale ) );
        pat->setPosition( pos );
    }
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createSprite( osg::Group *parent )
{
    osg::ref_ptr<osg::Billboard> billboard = new osg::Billboard();
    parent->addChild( billboard.get() );

    billboard->setMode( osg::Billboard::AXIAL_ROT );
    billboard->setNormal( osg::Vec3f( 0.0f, 1.0f, 0.0f ) );

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
    billboard->addDrawable( geometry.get(), osg::Vec3( 0.0, 0.0, 0.0 ) );

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();

    v->push_back( osg::Vec3f( -1.0f, 0.0f,  0.0f ) );
    v->push_back( osg::Vec3f(  1.0f, 0.0f,  0.0f ) );
    v->push_back( osg::Vec3f(  1.0f, 0.0f, -1.0f ) );
    v->push_back( osg::Vec3f( -1.0f, 0.0f, -1.0f ) );

    createQuad( geometry.get(), v.get(), true );

    osg::ref_ptr<osg::StateSet> billboardStateSet = billboard->getOrCreateStateSet();

    // texture
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
    texture->setImage( osgDB::readImageFile( "../00_data/cloud.png" ) );
    billboardStateSet->setTextureAttributeAndModes( 0, texture.get(), osg::StateAttribute::ON );

    // material
    osg::ref_ptr<osg::Material> material = new osg::Material();
    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    material->setAmbient( osg::Material::FRONT, osg::Vec4f( 0.8f, 0.8f, 0.8f, 1.0f ) );
    material->setDiffuse( osg::Material::FRONT, osg::Vec4f( 1.0f, 1.0f, 1.0f, 1.0f ) );
    billboardStateSet->setAttribute( material.get() );

    // alpha blending
    osg::ref_ptr<osg::AlphaFunc> alphaFunc = new osg::AlphaFunc();
    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();
    blendFunc->setFunction( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    alphaFunc->setFunction( osg::AlphaFunc::GEQUAL, 0.05 );
    billboardStateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    billboardStateSet->setAttributeAndModes( blendFunc.get(), osg::StateAttribute::ON );
    billboardStateSet->setAttributeAndModes( alphaFunc.get(), osg::StateAttribute::ON );
    billboardStateSet->setMode( GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE );
    billboardStateSet->setRenderBinDetails( 3, "DepthSortedBin" );
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createQuad( osg::Geometry *geom, osg::Vec3Array *v,
                            bool texCoords, bool color, float alpha )
{
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec2Array> t = new osg::Vec2Array();
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();

    osg::Vec3d tmp = ( v->at( 1 ) - v->at( 0 ) ) ^ ( v->at( 2 ) - v->at( 0 ) );
    tmp.normalize();
    n->push_back( tmp );

    c->push_back( osg::Vec4( 1.0f, 1.0f, 1.0f, alpha ) );

    geom->setVertexArray( v );
    geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::TRIANGLE_FAN, 0, v->size() ) );

    geom->setNormalArray( n.get() );
    geom->setNormalBinding( osg::Geometry::BIND_OVERALL );

    if ( color )
    {
        geom->setColorArray( c.get() );
        geom->setColorBinding( osg::Geometry::BIND_OVERALL );
    }

    if ( texCoords )
    {
        t->push_back( osg::Vec2( 0, 0 ) );
        t->push_back( osg::Vec2( 1, 0 ) );
        t->push_back( osg::Vec2( 1, 1 ) );
        t->push_back( osg::Vec2( 0, 1 ) );

        geom->setTexCoordArray( 0, t.get() );
    }
}
