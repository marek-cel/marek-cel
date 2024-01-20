#include <SceneRoot.h>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Program>
#include <osg/Shader>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#include <osg/Texture3D>
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

    createSphere1();
    createSphere2();
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot() {}

////////////////////////////////////////////////////////////////////////////////

osg::Geode* SceneRoot::createSphere( osg::Vec3f origin )
{
    osg::Geode *geode = new osg::Geode();
    _root->addChild( geode );
    osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere( origin, 100.0f );
    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( sphere.get() );
    geode->addDrawable( shape.get() );

    return geode;
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createSphere1()
{
    osg::ref_ptr<osg::Geode> geode = createSphere( osg::Vec3f( -100.0, 0.0, 0.0) );

    osg::StateSet* stateSet = geode->getOrCreateStateSet();

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage(osgDB::readImageFile("../data/" + _textureBaseName + "_Color.jpg"));

    stateSet->setTextureAttributeAndModes( 0, texture.get(), osg::StateAttribute::ON );
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::createSphere2()
{
    osg::ref_ptr<osg::Geode> geode = createSphere( osg::Vec3f( 100.0, 0.0, 0.0) );
    attachShader( geode.get() );
}

////////////////////////////////////////////////////////////////////////////////

void SceneRoot::attachShader( osg::Geode *geode )
{
    // Load the shaders from external text files
    osg::ref_ptr<osg::Shader> vertShader = new osg::Shader(osg::Shader::VERTEX);
    vertShader->loadShaderSourceFromFile("../src/shader.vert");

    osg::ref_ptr<osg::Shader> fragShader = new osg::Shader(osg::Shader::FRAGMENT);
    fragShader->loadShaderSourceFromFile("../src/shader.frag");

    // Compile the shaders into a program
    osg::ref_ptr<osg::Program> program = new osg::Program();
    program->addShader(vertShader);
    program->addShader(fragShader);

    osg::StateSet* stateSet = geode->getOrCreateStateSet();

    osg::ref_ptr<osg::Image> albedoImg    = osgDB::readImageFile("../data/" + _textureBaseName + "_Color.jpg"            );
    osg::ref_ptr<osg::Image> roughnessImg = osgDB::readImageFile("../data/" + _textureBaseName + "_Roughness.jpg"        );
    osg::ref_ptr<osg::Image> metallicImg  = osgDB::readImageFile("../data/" + _textureBaseName + "_Metalness.jpg"        );
    osg::ref_ptr<osg::Image> normalImg    = osgDB::readImageFile("../data/" + _textureBaseName + "_NormalGL.jpg"         );
    osg::ref_ptr<osg::Image> heightImg    = osgDB::readImageFile("../data/" + _textureBaseName + "_Displacement.jpg"     );
    osg::ref_ptr<osg::Image> aoImg        = osgDB::readImageFile("../data/" + _textureBaseName + "_AmbientOcclusion.jpg" );

    if ( !albedoImg    .valid() ) { std::cerr << "Invalid albedo texture file!"            << std::endl; exit(-1); }
    if ( !roughnessImg .valid() ) { std::cerr << "Invalid roughness texture file!"         << std::endl; exit(-1); }
    if ( !metallicImg  .valid() ) { std::cerr << "Invalid metallic texture file!"          << std::endl; exit(-1); }
    if ( !normalImg    .valid() ) { std::cerr << "Invalid normal texture file!"            << std::endl; exit(-1); }
    if ( !heightImg    .valid() ) { std::cerr << "Invalid height texture file!"            << std::endl; exit(-1); }
    if ( !aoImg        .valid() ) { std::cerr << "Invalid ambient occlusion texture file!" << std::endl; exit(-1); }

    osg::ref_ptr<osg::Texture2D> albedoMap    = new osg::Texture2D;
    osg::ref_ptr<osg::Texture2D> roughnessMap = new osg::Texture2D;
    osg::ref_ptr<osg::Texture2D> metallicMap  = new osg::Texture2D;
    osg::ref_ptr<osg::Texture2D> normalMap    = new osg::Texture2D;
    osg::ref_ptr<osg::Texture2D> heightMap    = new osg::Texture2D;
    osg::ref_ptr<osg::Texture2D> aoMap        = new osg::Texture2D;

    albedoMap    ->setImage( albedoImg    );
    roughnessMap ->setImage( roughnessImg );
    metallicMap  ->setImage( metallicImg  );
    normalMap    ->setImage( normalImg    );
    heightMap    ->setImage( heightImg    );
    aoMap        ->setImage( aoImg        );
}
