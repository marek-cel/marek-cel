#include <fstream>
#include <iostream>
#include <sstream>

#include <osg/ArgumentParser>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>

#include <osgDB/ReadFile>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/SphericalManipulator>

// Vertex Shader
const char* vertCode = R"(
#version 110

varying vec3 vNormal;
varying vec3 vPosition;
varying vec3 vViewPosition;
varying vec2 vTexCoord;

void main()
{
    // Transform vertex position to eye space
    vViewPosition = vec3(gl_ModelViewMatrix * gl_Vertex);

    // Transform position to world space for lighting calculations
    vPosition = vec3(gl_ModelViewMatrix * gl_Vertex);

    // Transform normal to eye space
    vNormal = normalize(gl_NormalMatrix * gl_Normal);

    // Pass through texture coordinates
    vTexCoord = gl_MultiTexCoord0.xy;

    gl_Position = ftransform();
}
)";

// Fragment Shader
const char* fragCode = R"(
#version 110

varying vec3 vNormal;
varying vec3 vPosition;
varying vec3 vViewPosition;
varying vec2 vTexCoord;

uniform sampler2D texture0;

void main()
{
    // Sample the texture
    vec3 textureColor = texture2D(texture0, vTexCoord).rgb;

    // Material properties - now modulated by texture
    vec3 materialAmbient = vec3(0.2, 0.2, 0.2) * textureColor;
    vec3 materialDiffuse = textureColor;
    vec3 materialSpecular = vec3(0.3, 0.3, 0.3);
    float materialShininess = 32.0;

    // Light properties (from OpenGL fixed pipeline light 0)
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightPosition = vec3(gl_LightSource[0].position);

    // Normalize the normal vector
    vec3 normal = normalize(vNormal);

    // Calculate light direction
    vec3 lightDir = normalize(lightPosition - vPosition);

    // Calculate view direction (towards camera)
    vec3 viewDir = normalize(-vViewPosition);

    // Calculate reflection direction
    vec3 reflectDir = reflect(-lightDir, normal);

    // Ambient component
    vec3 ambient = materialAmbient * lightColor;

    // Diffuse component
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * materialDiffuse * lightColor;

    // Specular component
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular = spec * materialSpecular * lightColor;

    // Combine all components
    vec3 result = ambient + diffuse + specular;

    gl_FragColor = vec4(result, 1.0);
}
)";

void setupCameraManipulators(osgViewer::Viewer* viewer, osg::ArgumentParser* arguments)
{
    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManip = new osgGA::KeySwitchMatrixManipulator();

    keyswitchManip->addMatrixManipulator( '1', "Trackball"   , new osgGA::TrackballManipulator()   );
    keyswitchManip->addMatrixManipulator( '2', "Flight"      , new osgGA::FlightManipulator()      );
    keyswitchManip->addMatrixManipulator( '3', "Drive"       , new osgGA::DriveManipulator()       );
    keyswitchManip->addMatrixManipulator( '4', "Terrain"     , new osgGA::TerrainManipulator()     );
    keyswitchManip->addMatrixManipulator( '5', "Orbit"       , new osgGA::OrbitManipulator()       );
    keyswitchManip->addMatrixManipulator( '6', "FirstPerson" , new osgGA::FirstPersonManipulator() );
    keyswitchManip->addMatrixManipulator( '7', "Spherical"   , new osgGA::SphericalManipulator()   );

    std::string pathfile;
    double animationSpeed = 1.0;
    while(arguments->read("--speed",animationSpeed) ) {}
    char keyForAnimationPath = '8';
    while (arguments->read("-p",pathfile))
    {
        osgGA::AnimationPathManipulator* apm = new osgGA::AnimationPathManipulator(pathfile);
        if (apm || !apm->valid())
        {
            apm->setTimeScale(animationSpeed);

            unsigned int num = keyswitchManip->getNumMatrixManipulators();
            keyswitchManip->addMatrixManipulator(keyForAnimationPath, "Path", apm);
            keyswitchManip->selectMatrixManipulator(num);
            ++keyForAnimationPath;
        }
    }

    viewer->setCameraManipulator(keyswitchManip.get());
}

void setupEventHandlers(osgViewer::Viewer* viewer, osg::ArgumentParser* arguments)
{
    // add the state manipulator
    viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

    // add the thread model handler
    viewer->addEventHandler(new osgViewer::ThreadingHandler);

    // add the window size toggle handler
    viewer->addEventHandler(new osgViewer::WindowSizeHandler);

    // add the stats handler
    viewer->addEventHandler(new osgViewer::StatsHandler);

    // add the help handler
    viewer->addEventHandler(new osgViewer::HelpHandler(arguments->getApplicationUsage()));

    // add the record camera path handler
    viewer->addEventHandler(new osgViewer::RecordCameraPathHandler);

    // add the LOD Scale handler
    viewer->addEventHandler(new osgViewer::LODScaleHandler);

    // add the screen capture handler
    viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
}

osg::PositionAttitudeTransform* createLight(osg::Group* root)
{
    osg::ref_ptr<osg::PositionAttitudeTransform> lightPat = new osg::PositionAttitudeTransform();
    root->addChild(lightPat.get());

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();
    lightPat->addChild(lightSource.get());

    osg::ref_ptr<osg::Light> lightSun = new osg::Light();

    lightSun->setLightNum(0);

    osg::Vec4 color(1.0, 1.0, 1.0, 1.0);
    osg::Vec3d position(6.0, -2.0, 4.0);

    lightSun->setPosition(osg::Vec4d(position, 1.0));
    lightPat->setPosition(position);

    lightSun->setAmbient  ( color );
    lightSun->setDiffuse  ( color );
    lightSun->setSpecular ( color );

    lightSun->setConstantAttenuation(1.0);

    lightSource->setLight(lightSun.get());

    lightSource->setLocalStateSetModes(osg::StateAttribute::ON);
    lightSource->setStateSetModes(*root->getOrCreateStateSet(), osg::StateAttribute::ON);

    return lightPat.release();
}

osg::Texture2D* readTextureFromFile(const char* path)
{
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(path);
    if ( image.valid() )
    {
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
        texture->setImage(image.get());

        texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture::MIRROR);
        texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture::MIRROR);

        texture->setNumMipmapLevels(4);
        texture->setMaxAnisotropy(8.0);

        texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_NEAREST);
        texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);

        return texture.release();
    }
    else
    {
        std::cerr << "Cannot open file: " << path << std::endl;
    }

    return nullptr;
}

osg::Group* createScene()
{
    osg::ref_ptr<osg::Group> root = new osg::Group();

    osg::ref_ptr<osg::StateSet> stateSet = root->getOrCreateStateSet();
    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );

    createLight(root.get());

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    root->addChild(geode.get());

    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3f(), 10.0, 10.0, 10.0);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(box.get());
    geode->addDrawable(shape.get());

    osg::ref_ptr<osg::StateSet> geodeStateSet = geode->getOrCreateStateSet();

    osg::ref_ptr<osg::Texture2D> texture0 = readTextureFromFile("../../../data/DiamondPlate008C_1K_Color.jpg");
    if ( texture0.valid() )
    {
        geodeStateSet->setTextureAttributeAndModes(0, texture0, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode));
    geodeStateSet->setAttributeAndModes(program.get());
    geodeStateSet->addUniform(new osg::Uniform("texture0", 0));

    return root.release();
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    osg::ArgumentParser arguments(&argc, argv);

    osgViewer::Viewer viewer(arguments);

    setupCameraManipulators(&viewer, &arguments);
    setupEventHandlers(&viewer, &arguments);

    viewer.setUpViewInWindow(0, 0, 800, 600);
    viewer.setSceneData(createScene());

    return viewer.run();
}