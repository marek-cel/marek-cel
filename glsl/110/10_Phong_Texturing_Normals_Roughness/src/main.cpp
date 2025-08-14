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
    vViewPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
    vPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
    vNormal = normalize(gl_NormalMatrix * gl_Normal);
    vTexCoord = gl_MultiTexCoord0.xy;

    gl_Position = ftransform();
}
)";

// Fragment Shader
const char* fragCode = R"(
#version 110

varying vec3 vNormal;
varying vec3 vPosition;      // eye space
varying vec3 vViewPosition;  // eye space
varying vec2 vTexCoord;

uniform sampler2D textureColorMap;
uniform sampler2D textureNormalMap;
uniform sampler2D textureRoughnessMap; // bound to unit 2 in your C++

vec3 normalFromMap(in vec2 uv, in vec3 Ns, in vec3 P)
{
    // Build TBN from derivatives (no vertex tangents needed)
    vec3 dp1  = dFdx(P);
    vec3 dp2  = dFdy(P);
    vec2 duv1 = dFdx(uv);
    vec2 duv2 = dFdy(uv);

    float det = duv1.x * duv2.y - duv1.y * duv2.x;
    float invDet = (abs(det) > 1e-8) ? (1.0 / det) : 0.0;

    vec3 T = normalize( (dp1 * duv2.y - dp2 * duv1.y) * invDet );
    vec3 B = normalize( (dp2 * duv1.x - dp1 * duv2.x) * invDet );

    vec3 nTex = texture2D(textureNormalMap, uv).xyz * 2.0 - 1.0;
    // If you ever use a DirectX-style normal map, uncomment:
    // nTex.g = -nTex.g;

    mat3 TBN = mat3(T, B, normalize(Ns));
    return normalize(TBN * nTex);
}

void main()
{
    // Albedo
    vec3 baseColor = texture2D(textureColorMap, vTexCoord).rgb;

    // Roughness: 0 = smooth (tight, strong spec), 1 = rough (broad, weak spec)
    float roughness = texture2D(textureRoughnessMap, vTexCoord).r;
    roughness = clamp(roughness, 0.0, 1.0);

    // Convert to a "gloss" control; square to bias toward smoother highlights
    float gloss = 1.0 - roughness;
    float specIntensity = gloss * gloss;                 // scales specular color
    float materialShininess = mix(8.0, 256.0, specIntensity); // Phong exponent

    // Material
    vec3 materialAmbient  = vec3(0.2) * baseColor;
    vec3 materialDiffuse  = baseColor;
    vec3 materialSpecular = vec3(0.3) * specIntensity; // dimmer when rough

    // Light 0 (eye space)
    vec3 lightColor    = vec3(1.0);
    vec3 lightPosition = vec3(gl_LightSource[0].position);

    // Normal mapping
    vec3 N = normalFromMap(vTexCoord, normalize(vNormal), vPosition);

    // Phong shading (eye space)
    vec3 L = normalize(lightPosition - vPosition);
    vec3 V = normalize(-vViewPosition);
    vec3 R = reflect(-L, N);

    // Ambient
    vec3 ambient = materialAmbient * lightColor;

    // Diffuse
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diff * materialDiffuse * lightColor;

    // Specular
    float spec = pow(max(dot(V, R), 0.0), materialShininess);
    vec3 specular = spec * materialSpecular * lightColor;

    gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
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

    // add sphere representing light source
    osg::ref_ptr<osg::Sphere> lightSphere = new osg::Sphere(position, 0.1);
    osg::ref_ptr<osg::ShapeDrawable> lightDrawable = new osg::ShapeDrawable(lightSphere.get());
    lightDrawable->setColor(osg::Vec4(1.0, 1.0, 0.0, 1.0)); // yellow color
    lightPat->addChild(lightDrawable.get());

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

    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3f(), 5.0, 5.0, 5.0);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(box.get());
    geode->addDrawable(shape.get());

    osg::ref_ptr<osg::StateSet> geodeStateSet = geode->getOrCreateStateSet();

    osg::ref_ptr<osg::Texture2D> textureColorMap = readTextureFromFile("../../../data/DiamondPlate008C_1K_Color.jpg");
    if ( textureColorMap.valid() )
    {
        geodeStateSet->setTextureAttributeAndModes(0, textureColorMap, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Texture2D> textureNormalMap = readTextureFromFile("../../../data/DiamondPlate008C_1K_NormalGL.jpg");
    if ( textureNormalMap.valid() )
    {
        geodeStateSet->setTextureAttributeAndModes(1, textureNormalMap, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Texture2D> textureRoughnessMap = readTextureFromFile("../../../data/DiamondPlate008C_1K_Roughness.jpg");
    if ( textureRoughnessMap.valid() )
    {
        geodeStateSet->setTextureAttributeAndModes(2, textureRoughnessMap, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode));
    geodeStateSet->setAttributeAndModes(program.get());
    geodeStateSet->addUniform(new osg::Uniform("textureColorMap", 0));
    geodeStateSet->addUniform(new osg::Uniform("textureNormalMap", 1));
    geodeStateSet->addUniform(new osg::Uniform("textureRoughnessMap", 2));

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