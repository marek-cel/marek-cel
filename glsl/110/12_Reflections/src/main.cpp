#include <fstream>
#include <iostream>
#include <sstream>

#include <osg/ArgumentParser>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/Material>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/SphericalManipulator>

#include <osgDB/ReadFile>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

const float skyRadius = 20.0f;
const osg::Vec3 lightPosition(
    skyRadius * cos(osg::DegreesToRadians(54.0)),
    0.0,
    skyRadius * sin(osg::DegreesToRadians(54.0))
);


void setupCameraManipulators(osgViewer::Viewer* viewer, osg::ArgumentParser* arguments);

void setupEventHandlers(osgViewer::Viewer* viewer, osg::ArgumentParser* arguments);

osg::Texture2D* readTextureFromFile(const char* path);

enum class Projection
{
    Azimuthal = 0,  ///< azimuthal projection
    Cylindrical     ///< cylindrical projection
};

void createDome(osg::Geometry* geom, double radius,
                bool texCoords = false, Projection projection = Projection::Cylindrical,
                int lat_segments = 18, int lon_segments = 36);

// Vertex Shader
const char* vertCode = R"(
#version 120

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
#version 120

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

void createLight(osg::Group* root)
{
    osg::ref_ptr<osg::PositionAttitudeTransform> lightPat = new osg::PositionAttitudeTransform();
    root->addChild(lightPat.get());

    osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource();
    lightPat->addChild(lightSource.get());

    osg::ref_ptr<osg::Light> lightSun = new osg::Light();

    lightSun->setLightNum(0);

    osg::Vec4 color(1.0, 1.0, 1.0, 1.0);

    lightSun->setPosition(osg::Vec4d(lightPosition, 1.0));
    lightPat->setPosition(lightPosition);

    lightSun->setAmbient  ( color );
    lightSun->setDiffuse  ( color );
    lightSun->setSpecular ( color );

    lightSun->setConstantAttenuation(1.0);

    lightSource->setLight(lightSun.get());

    lightSource->setLocalStateSetModes(osg::StateAttribute::ON);
    lightSource->setStateSetModes(*root->getOrCreateStateSet(), osg::StateAttribute::ON);

    // add sphere representing light source
    osg::ref_ptr<osg::Sphere> lightSphere = new osg::Sphere(lightPosition, 1.0);
    osg::ref_ptr<osg::ShapeDrawable> lightDrawable = new osg::ShapeDrawable(lightSphere.get());
    lightDrawable->setColor(osg::Vec4(1.0, 1.0, 0.0, 1.0)); // yellow color
    lightPat->addChild(lightDrawable.get());
}

void createSky(osg::Group* root)
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    root->addChild(geode.get());

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
    geode->addDrawable(geom.get());

    createDome(geom, 2.0 * skyRadius, true, Projection::Cylindrical, 18, 36);

    osg::ref_ptr<osg::StateSet> state_set = geode->getOrCreateStateSet();

    osg::ref_ptr<osg::Material> material = new osg::Material();
    material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    material->setAmbient(osg::Material::BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
    material->setDiffuse(osg::Material::BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));
    state_set->setAttribute(material.get());

    osg::ref_ptr<osg::Texture2D> texture = readTextureFromFile("../../../data/sky.jpg");
    state_set->setTextureAttributeAndModes(0, texture.get(), osg::StateAttribute::ON);
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
    createSky(root.get());

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    root->addChild(geode.get());

    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3f(), 5.0, 5.0, 5.0);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(box.get());
    geode->addDrawable(shape.get());

    osg::ref_ptr<osg::StateSet> geodeStateSet = geode->getOrCreateStateSet();

    osg::ref_ptr<osg::Texture2D> textureColorMap = readTextureFromFile("../../../data/Metal002_1K-JPG_Color.jpg");
    if ( textureColorMap.valid() )
    {
        geodeStateSet->setTextureAttributeAndModes(0, textureColorMap, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Texture2D> textureNormalMap = readTextureFromFile("../../../data/Metal002_1K-JPG_NormalGL.jpg");
    if ( textureNormalMap.valid() )
    {
        geodeStateSet->setTextureAttributeAndModes(1, textureNormalMap, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Texture2D> textureRoughnessMap = readTextureFromFile("../../../data/Metal002_1K-JPG_Roughness.jpg");
    if ( textureRoughnessMap.valid() )
    {
        geodeStateSet->setTextureAttributeAndModes(2, textureRoughnessMap, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Texture2D> textureMetlnessMap = readTextureFromFile("../../../data/Metal002_1K-JPG_Metalness.jpg");
    if ( textureMetlnessMap.valid() )
    {
        geodeStateSet->setTextureAttributeAndModes(3, textureMetlnessMap, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode));
    geodeStateSet->setAttributeAndModes(program.get());
    geodeStateSet->addUniform(new osg::Uniform("textureColorMap", 0));
    geodeStateSet->addUniform(new osg::Uniform("textureNormalMap", 1));
    geodeStateSet->addUniform(new osg::Uniform("textureRoughnessMap", 2));
    geodeStateSet->addUniform(new osg::Uniform("textureMetlnessMap", 3));

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