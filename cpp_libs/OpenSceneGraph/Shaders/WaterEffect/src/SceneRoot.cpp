#include <osg/ClipNode>
#include <osg/Geode>
#include <osg/MatrixTransform>
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
    osg::ref_ptr<osg::Geode> geodeBox = new osg::Geode();

    osg::ref_ptr<osg::Box> box = new osg::Box( osg::Vec3f(), 1.0f, 1.0f, 1.0f );

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( box.get() );
    geodeBox->addDrawable( shape.get() );

    float z = -1.0f;
    osg::ref_ptr<osg::MatrixTransform> reverse = new osg::MatrixTransform;
    reverse->preMult(osg::Matrix::translate(0.0f, 0.0f, -z) *
                     osg::Matrix::scale(1.0f, 1.0f, -1.0f) *
                     osg::Matrix::translate(0.0f, 0.0f, z) );
    reverse->addChild( geodeBox.get() );

    osg::ref_ptr<osg::ClipPlane> clipPlane = new osg::ClipPlane;
    clipPlane->setClipPlane( 0.0, 0.0, -1.0, z );
    clipPlane->setClipPlaneNum( 0 );

    osg::ref_ptr<osg::ClipNode> clipNode = new osg::ClipNode;
    clipNode->addClipPlane( clipPlane.get() );
    clipNode->addChild( reverse.get() );

    ////////////////////////////////

    // The RTT camera
    osg::ref_ptr<osg::Texture2D> tex2D = new osg::Texture2D();
    tex2D->setTextureSize( 1024, 1024 );
    tex2D->setInternalFormat( GL_RGBA );
    tex2D->setFilter( osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR );
    tex2D->setFilter( osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR );

    osg::ref_ptr<osg::Camera> cameraRTT = new osg::Camera();

    cameraRTT->setClearColor( osg::Vec4() );
    cameraRTT->setClearMask( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    cameraRTT->setRenderTargetImplementation( osg::Camera::FRAME_BUFFER_OBJECT );
    cameraRTT->setRenderOrder( osg::Camera::PRE_RENDER );

    cameraRTT->setViewport( 0, 0, tex2D->getTextureWidth(), tex2D->getTextureHeight() );
    cameraRTT->attach( osg::Camera::COLOR_BUFFER, tex2D.get() );

    cameraRTT->addChild( clipNode.get() );

    // The water plane
    const osg::Vec3& center = geodeBox->getBound().center();
    float planeSize = 20.0f * geodeBox->getBound().radius();

    osg::Vec3 planeCorner( center.x() - 0.5f*planeSize, center.y() - 0.5f*planeSize, z );

    osg::ref_ptr<osg::Geometry> quad = osg::createTexturedQuadGeometry(
                planeCorner,
                osg::Vec3( planeSize, 0.0f, 0.0f ),
                osg::Vec3( 0.0f, planeSize, 0.0f ) );

    osg::ref_ptr<osg::Geode> geodeQuad = new osg::Geode;
    geodeQuad->addDrawable( quad.get() );

    osg::ref_ptr<osg::Texture2D> texSkyMap = new osg::Texture2D();
    texSkyMap->setImage( osgDB::readImageFile( "../../00_data/skymap.jpg" ) );
    texSkyMap->setWrap( osg::Texture::WRAP_S, osg::Texture::REPEAT );
    texSkyMap->setWrap( osg::Texture::WRAP_T, osg::Texture::REPEAT );
    texSkyMap->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR );
    texSkyMap->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );

    osg::ref_ptr<osg::Texture2D> texWaterDUDV = new osg::Texture2D();
    texWaterDUDV->setImage( osgDB::readImageFile( "../../00_data/water_DUDV.jpg" ) );
    texWaterDUDV->setWrap( osg::Texture::WRAP_S, osg::Texture::REPEAT );
    texWaterDUDV->setWrap( osg::Texture::WRAP_T, osg::Texture::REPEAT );
    texWaterDUDV->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR );
    texWaterDUDV->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );

    osg::ref_ptr<osg::Texture2D> texWaterNM = new osg::Texture2D();
    texWaterNM->setImage( osgDB::readImageFile( "../../00_data/water_NM.jpg" ) );
    texWaterNM->setWrap( osg::Texture::WRAP_S, osg::Texture::REPEAT );
    texWaterNM->setWrap( osg::Texture::WRAP_T, osg::Texture::REPEAT );
    texWaterNM->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR );
    texWaterNM->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );

    osg::ref_ptr<osg::StateSet> stateSet = geodeQuad->getOrCreateStateSet();
    stateSet->setTextureAttributeAndModes( 0, tex2D.get() );
    stateSet->setTextureAttributeAndModes( 1, texSkyMap.get() );
    stateSet->setTextureAttributeAndModes( 2, texWaterDUDV.get() );
    stateSet->setTextureAttributeAndModes( 3, texWaterNM.get() );

    osg::ref_ptr<osg::Program> program = new osg::Program();
    program->addShader( new osg::Shader( osg::Shader::VERTEX   , shader_vert ) );
    program->addShader( new osg::Shader( osg::Shader::FRAGMENT , shader_frag ) );
    stateSet->setAttributeAndModes( program.get() );
    stateSet->addUniform( new osg::Uniform("reflection", 0) );
    stateSet->addUniform( new osg::Uniform("defaultTex", 1) );
    stateSet->addUniform( new osg::Uniform("refraction", 2) );
    stateSet->addUniform( new osg::Uniform("normalTex", 3) );

    ////////////////////////////////

    m_root->addChild( geodeBox.get() );
    m_root->addChild( cameraRTT.get() );
    m_root->addChild( geodeQuad.get() );
}
