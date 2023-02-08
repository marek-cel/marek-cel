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

    create();
    createRef();
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot() {}

void SceneRoot::create()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild( geode.get() );
    osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere( osg::Vec3f(), 100.0f );
    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( sphere.get() );
    geode->addDrawable( shape.get() );

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

    osg::ref_ptr<osg::Texture2D> albedoTexture = new osg::Texture2D;
    albedoTexture->setImage(osgDB::readImageFile("../data/" + _textureBaseName + "_Color.jpg"));

    osg::ref_ptr<osg::Texture2D> roughnessTexture = new osg::Texture2D;
    roughnessTexture->setImage(osgDB::readImageFile("../data/" + _textureBaseName + "_Roughness.jpg"));

    osg::ref_ptr<osg::Texture2D> metallicTexture = new osg::Texture2D;
    metallicTexture->setImage(osgDB::readImageFile("../data/" + _textureBaseName + "_Metalness.jpg"));

    osg::ref_ptr<osg::Texture2D> normalTexture = new osg::Texture2D;
    normalTexture->setImage(osgDB::readImageFile("../data/" + _textureBaseName + "_NormalGL.jpg"));

    osg::ref_ptr<osg::Texture2D> heightTexture = new osg::Texture2D;
    heightTexture->setImage(osgDB::readImageFile("../data/" + _textureBaseName + "_Displacement.jpg"));

    osg::ref_ptr<osg::Texture2D> ambientOcclusionTexture = new osg::Texture2D;
    ambientOcclusionTexture->setImage(osgDB::readImageFile("../data/" + _textureBaseName + "_AmbientOcclusion.jpg"));

    osg::ref_ptr<osg::Uniform> albedoTextureUniform           = new osg::Uniform( "albedoTexture"           , albedoTexture    );
    osg::ref_ptr<osg::Uniform> roughnessTextureUniform        = new osg::Uniform( "roughnessTexture"        , roughnessTexture );
    osg::ref_ptr<osg::Uniform> metallicTextureUniform         = new osg::Uniform( "metallicTexture"         , metallicTexture  );
    osg::ref_ptr<osg::Uniform> normalTextureUniform           = new osg::Uniform( "normalTexture"           , normalTexture    );
    osg::ref_ptr<osg::Uniform> heightTextureUniform           = new osg::Uniform( "heightTexture"           , heightTexture    );
    osg::ref_ptr<osg::Uniform> ambientOcclusionTextureUniform = new osg::Uniform( "ambientOcclusionTexture" , ambientOcclusionTexture    );

    stateSet->addUniform( albedoTextureUniform.get() );
    stateSet->addUniform( roughnessTextureUniform.get() );
    stateSet->addUniform( metallicTextureUniform.get() );
    stateSet->addUniform( normalTextureUniform.get() );
    stateSet->addUniform( heightTextureUniform.get() );
    stateSet->addUniform( ambientOcclusionTextureUniform.get() );


    stateSet->setAttributeAndModes(program.get());
    stateSet->setTextureAttributeAndModes(0, albedoTexture);
    stateSet->setTextureAttributeAndModes(1, roughnessTexture);
    stateSet->setTextureAttributeAndModes(2, metallicTexture);
    stateSet->setTextureAttributeAndModes(3, normalTexture);
    stateSet->setTextureAttributeAndModes(4, heightTexture);
    stateSet->setTextureAttributeAndModes(5, ambientOcclusionTexture);
}

void SceneRoot::createRef()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild( geode.get() );
    osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere( osg::Vec3f( 200.0, 0.0, 0.0 ), 100.0f );
    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( sphere.get() );
    geode->addDrawable( shape.get() );

    osg::StateSet* stateSet = geode->getOrCreateStateSet();

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage(osgDB::readImageFile("../data/" + _textureBaseName + "_Color.jpg"));

    stateSet->setTextureAttributeAndModes( 0, texture.get(), osg::StateAttribute::ON );
}
