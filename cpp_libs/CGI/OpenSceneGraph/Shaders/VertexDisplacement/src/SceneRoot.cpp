#include <osg/Geode>
#include <osg/Program>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>

#include <osgDB/ReadFile>

#include <SceneRoot.h>

////////////////////////////////////////////////////////////////////////////////

extern char shader_vert[];
extern char shader_frag[];

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

    create();
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot() {}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::create()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    m_root->addChild( geode.get() );

    const unsigned int r = 512;
    const unsigned int c = 512;

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array( c * r );
    osg::ref_ptr<osg::Vec2Array> t = new osg::Vec2Array( c * r );

    for ( unsigned int i = 0; i < r; i++ )
    {
        for ( unsigned int j = 0; j < c; j++ )
        {
            (*v)[ i*c + j ].set( (float)i, (float)j, 0.0f );
            (*t)[ i*c + j ].set( (float)i/(float)r, (float)j/(float)c );
        }
    }

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
    geode->addDrawable( geom.get() );

    geom->setUseDisplayList( false );
    geom->setUseVertexBufferObjects( true );
    geom->setVertexArray( v.get() );
    geom->setTexCoordArray( 0, t.get() );

    for ( unsigned int i = 0; i < r - 1; i++ )
    {
        osg::ref_ptr<osg::DrawElementsUInt> de = new osg::DrawElementsUInt( GL_QUAD_STRIP, c*2 );

        for ( unsigned int j = 0; j < c; j++ )
        {
            (*de)[ j*2 + 0 ] = i*c + j;
            (*de)[ j*2 + 1 ] = ( i + 1 )*c + j;
        }

        geom->addPrimitiveSet( de.get() );
    }

    geom->setInitialBound( osg::BoundingBox(-1.0f,-1.0f,-100.0f, 1.0f, 1.0f, 100.0f) );

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
    texture->setImage( osgDB::readImageFile( "../../osg256.png" ) );
    texture->setFilter( osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR );
    texture->setFilter( osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR );

    osg::ref_ptr<osg::Program> program = new osg::Program();
    program->addShader( new osg::Shader( osg::Shader::VERTEX   , shader_vert ) );
    program->addShader( new osg::Shader( osg::Shader::FRAGMENT , shader_frag ) );

    osg::ref_ptr<osg::StateSet> stateSet = m_root->getOrCreateStateSet();
    stateSet->addUniform( new osg::Uniform( "defaultTex", 0 ) );
    stateSet->setAttributeAndModes( program.get() );

    stateSet->setTextureAttributeAndModes( 0, texture.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE );
}
