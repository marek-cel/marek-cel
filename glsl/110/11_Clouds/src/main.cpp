/**
 * Basic volumetric cloud example.
 *
 * The program creates a single simplified static cumulus humilis cloud.
 * This program is intended to be used in real time rendering applications on
 * a relatively low spec hardware (integrated graphics).
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <osg/ArgumentParser>
#include <osg/CullFace>
#include <osg/Depth>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/LineWidth>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

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

const osg::Vec3 lightPosition(50.0f, -100.0f, 200.0f);
const osg::Vec3 lightColor(1.0f, 1.0f, 1.0f);

const char* vertCode = R"(
#version 120

varying vec3 vPosOS; // object-space position at the fragment

void main()
{
    vPosOS = gl_Vertex.xyz; // because our Box is defined in object space (-1..1)
    gl_Position = ftransform(); // fixed-function transform
}
)";

const char* fragCode = R"(
#version 120

varying vec3 vPosOS;

uniform vec3 uCamPosOS;   // camera position in *object* space
uniform float uDensity;   // overall density multiplier
uniform int uSteps;       // march steps (e.g., 12–16)
uniform float uStepMul;   // step length multiplier (e.g., 1.0/float(uSteps))

// Simple 3D noise function
float hash(vec3 p) {
    p = fract(p * 0.3183099 + 0.1);
    p *= 17.0;
    return fract(p.x * p.y * p.z * (p.x + p.y + p.z));
}

float noise(vec3 x) {
    vec3 i = floor(x);
    vec3 f = fract(x);
    f = f * f * (3.0 - 2.0 * f);

    return mix(mix(mix(hash(i + vec3(0, 0, 0)),
                       hash(i + vec3(1, 0, 0)), f.x),
                   mix(hash(i + vec3(0, 1, 0)),
                       hash(i + vec3(1, 1, 0)), f.x), f.y),
               mix(mix(hash(i + vec3(0, 0, 1)),
                       hash(i + vec3(1, 0, 1)), f.x),
                   mix(hash(i + vec3(0, 1, 1)),
                       hash(i + vec3(1, 1, 1)), f.x), f.y), f.z);
}

// Fractional Brownian Motion (fBm) for more complex noise
float fbm(vec3 p) {
    float value = 0.0;
    float amplitude = 0.5;
    float frequency = 1.0;

    for (int i = 0; i < 4; i++) {
        value += amplitude * noise(p * frequency);
        amplitude *= 0.5;
        frequency *= 2.0;
    }
    return value;
}

// Cloud density function
float cloudDensity(vec3 p) {
    // Basic sphere falloff
    float dist = length(p);
    if (dist > 1.0) return 0.0;

    float sphereFalloff = 1.0 - smoothstep(0.6, 1.0, dist);

    // Add noise for cloud shape
    vec3 noisePos = p * 2.0;
    float cloudNoise = fbm(noisePos);

    // Combine sphere and noise
    float density = sphereFalloff * cloudNoise;

    // Add some variation in height (make bottom more dense)
    density *= 1.0 + 0.3 * (1.0 - (p.y + 1.0) * 0.5);

    return max(0.0, density - 0.3); // threshold to create gaps
}

// Ray-sphere intersection for sphere at origin, radius 1
bool intersectUnitSphere(vec3 ro, vec3 rd, out float t0, out float t1)
{
    float b = dot(ro, rd);
    float c = dot(ro, ro) - 1.0;
    float disc = b*b - c;
    if (disc < 0.0) return false;
    float s = sqrt(disc);
    t0 = -b - s;
    t1 = -b + s;
    return t1 > 0.0; // there is an intersection in front
}

void main()
{
    // Entry point on the front faces ~ vPosOS (approx cube front entry)
    // Build ray from camera to entry point
    vec3 ro = uCamPosOS;
    vec3 rd = normalize(vPosOS - uCamPosOS);

    float t0, t1;
    if (!intersectUnitSphere(ro, rd, t0, t1)) discard; // miss the sphere

    // Clamp start to where the ray *enters* the sphere
    float t = max(t0, 0.0);
    float dt = (t1 - t) * uStepMul;

    vec3 col = vec3(1.0); // start with white
    float alpha = 0.0;

    // Front-to-back alpha compositing with noise-based density
    for (int i = 0; i < 64; ++i) // static upper bound for GLSL 1.20
    {
        if (i >= uSteps) break;

        vec3 p = ro + rd * (t + dt * float(i));

        float density = cloudDensity(p) * uDensity;
        float a = 1.0 - exp(-density * dt * 8.0); // Beer-Lambert absorption

        // front-to-back compositing
        col = mix(col, vec3(1.0), a * (1.0 - alpha));
        alpha += a * (1.0 - alpha);

        if (alpha >= 0.98) break; // early-out
    }

    gl_FragColor = vec4(col, alpha);
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
    viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));
    viewer->addEventHandler(new osgViewer::ThreadingHandler);
    viewer->addEventHandler(new osgViewer::WindowSizeHandler);
    viewer->addEventHandler(new osgViewer::StatsHandler);
    viewer->addEventHandler(new osgViewer::HelpHandler(arguments->getApplicationUsage()));
    viewer->addEventHandler(new osgViewer::RecordCameraPathHandler);
    viewer->addEventHandler(new osgViewer::LODScaleHandler);
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

    osg::Vec4 color(lightColor, 1.0f);

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
    osg::ref_ptr<osg::Sphere> lightSphere = new osg::Sphere(lightPosition, 10.0);
    osg::ref_ptr<osg::ShapeDrawable> lightDrawable = new osg::ShapeDrawable(lightSphere.get());
    lightDrawable->setColor(osg::Vec4(1.0, 1.0, 0.0, 1.0)); // yellow color
    lightPat->addChild(lightDrawable.get());

    return lightPat.release();
}

osg::Group* createBoxWireframe(const osg::Vec3& center, float size_x, float size_y, float size_z)
{
    osg::ref_ptr<osg::Group> wireframe = new osg::Group();

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    wireframe->addChild(geode.get());

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
    geode->addDrawable(geom.get());

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();

    v->push_back(osg::Vec3(center.x() - size_x, center.y() - size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() - size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() - size_x, center.y() + size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() + size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() - size_x, center.y() - size_y, center.z() + size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() - size_y, center.z() + size_z));
    v->push_back(osg::Vec3(center.x() - size_x, center.y() + size_y, center.z() + size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() + size_y, center.z() + size_z));

    v->push_back(osg::Vec3(center.x() - size_x, center.y() - size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() - size_x, center.y() - size_y, center.z() + size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() - size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() - size_y, center.z() + size_z));
    v->push_back(osg::Vec3(center.x() - size_x, center.y() + size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() - size_x, center.y() + size_y, center.z() + size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() + size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() + size_y, center.z() + size_z));

    v->push_back(osg::Vec3(center.x() - size_x, center.y() - size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() - size_x, center.y() + size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() - size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() + size_y, center.z() - size_z));
    v->push_back(osg::Vec3(center.x() - size_x, center.y() - size_y, center.z() + size_z));
    v->push_back(osg::Vec3(center.x() - size_x, center.y() + size_y, center.z() + size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() - size_y, center.z() + size_z));
    v->push_back(osg::Vec3(center.x() + size_x, center.y() + size_y, center.z() + size_z));

    n->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
    // magenta
    c->push_back(osg::Vec4(1.0f, 0.0f, 1.0f, 1.0f));

    geom->setVertexArray(v.get());
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size()));
    geom->setNormalArray(n.get());
    geom->setNormalBinding( osg::Geometry::BIND_OVERALL);
    geom->setColorArray(c.get());
    geom->setColorBinding(osg::Geometry::BIND_OVERALL);

    osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth();
    lineWidth->setWidth(2.0f);
    geode->getOrCreateStateSet()->setAttributeAndModes(lineWidth, osg::StateAttribute::ON);

    return wireframe.release();
}

struct CamPosUpdater : public osg::NodeCallback
{
    osgViewer::Viewer* viewer;
    osg::Uniform* uCamPosOS;

    CamPosUpdater(osgViewer::Viewer* v, osg::Uniform* camPos)
        : viewer(v), uCamPosOS(camPos) {}

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        // Update camera position (existing code)
        osg::Matrixd view = viewer->getCamera()->getViewMatrix();
        osg::Matrixd invView = osg::Matrixd::inverse(view);
        osg::Vec3d camWorld = osg::Vec3d(0.0, 0.0, 0.0) * invView;

        osg::Matrixd localToWorld;
        if (auto* mt = dynamic_cast<osg::MatrixTransform*>(node))
            localToWorld = mt->getMatrix();
        else
            localToWorld.makeIdentity();

        osg::Matrixd worldToLocal = osg::Matrixd::inverse(localToWorld);
        osg::Vec3d camObject = camWorld * worldToLocal;

        uCamPosOS->set(osg::Vec3(camObject));

        traverse(node, nv);
    }
};

osg::Group* createScene(osgViewer::Viewer* viewer)
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

    // --- Cloud proxy: cube enclosing a unit sphere ---
    osg::ref_ptr<osg::Geode> cloudGeode = new osg::Geode();
    osg::ref_ptr<osg::ShapeDrawable> cloudCube =
        new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.f, 0.f, 0.f), 2.f));
    // size=2 → unit radius sphere fits inside cube (-1..1)

    cloudGeode->addDrawable(cloudCube.get());

    // Place & scale the cloud node in world (adjust to your liking)
    osg::Matrix cloudXform = osg::Matrix::scale(osg::Vec3(150.0f, 150.0f, 80.0f)) *  // non-uniform later
                            osg::Matrix::translate(osg::Vec3(0.0f, 0.0f, 1.5f));
    osg::ref_ptr<osg::MatrixTransform> cloudMT = new osg::MatrixTransform(cloudXform);
    cloudMT->addChild(cloudGeode.get());
    root->addChild(cloudMT.get());

    osg::Matrixd localToWorld = cloudMT->getMatrix();
    osg::Matrixd worldToLocal = osg::Matrixd::inverse(localToWorld);

    osg::Vec3d lightObj = lightPosition * worldToLocal;   // into cloud's object space
    osg::Vec3  lightDir = osg::Vec3(lightObj) - osg::Vec3(0,0,0);
    lightDir.normalize();

    // small box at the origin
    // root->addChild(createBoxWireframe(osg::Vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f));
    // scaled up and translated box
    root->addChild(createBoxWireframe(osg::Vec3(0.0f, 0.0f, 1.5f), 150.0f, 150.0f, 80.0f));

    osg::ref_ptr<osg::StateSet> cloudStateSet = cloudMT->getOrCreateStateSet();

    // cloudStateSet->setMode(GL_CULL_FACE, osg::StateAttribute::ON);
    // osg::ref_ptr<osg::CullFace> cull = new osg::CullFace;
    // cull->setMode(osg::CullFace::BACK);  // draw only front faces
    // cloudStateSet->setAttributeAndModes(cull.get(), osg::StateAttribute::ON);

    // (optional) disable fixed-pipeline lighting on the proxy
    cloudStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    cloudStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
    cloudStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    cloudStateSet->setMode(GL_ALPHA_TEST, osg::StateAttribute::OFF);

    // (Optional) Soften depth sorting issues a bit:
    osg::ref_ptr<osg::Depth> depth = new osg::Depth;
    depth->setWriteMask(false); // don’t write depth (we’re translucent)
    cloudStateSet->setAttributeAndModes(depth.get(), osg::StateAttribute::ON);

    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode));
    cloudStateSet->setAttributeAndModes(program.get(), osg::StateAttribute::ON);

    // Uniforms
    osg::ref_ptr<osg::Uniform> uCamPosOS    = new osg::Uniform("uCamPosOS", osg::Vec3(0,0,0));
    osg::ref_ptr<osg::Uniform> uDensity     = new osg::Uniform("uDensity", 0.6f);
    osg::ref_ptr<osg::Uniform> uSteps       = new osg::Uniform("uSteps", 16); // increased steps for better quality
    osg::ref_ptr<osg::Uniform> uStepMul     = new osg::Uniform("uStepMul", 1.0f / 16.0f);
    osg::ref_ptr<osg::Uniform> uLightDirOS  = new osg::Uniform("uLightDirOS", lightDir);
    osg::ref_ptr<osg::Uniform> uLightColor  = new osg::Uniform("uLightColor", lightColor);
    osg::ref_ptr<osg::Uniform> uShadowSteps = new osg::Uniform("uShadowSteps", 6);
    osg::ref_ptr<osg::Uniform> uPhaseG      = new osg::Uniform("uPhaseG", 0.55f);
    osg::ref_ptr<osg::Uniform> uScatterMul  = new osg::Uniform("uScatterMul", 1.0f);

    cloudStateSet->addUniform(uCamPosOS.get());
    cloudStateSet->addUniform(uDensity.get());
    cloudStateSet->addUniform(uSteps.get());
    cloudStateSet->addUniform(uStepMul.get());
    cloudStateSet->addUniform(uLightDirOS.get());
    cloudStateSet->addUniform(uLightColor.get());
    cloudStateSet->addUniform(uShadowSteps.get());
    cloudStateSet->addUniform(uPhaseG.get());
    cloudStateSet->addUniform(uScatterMul.get());

    // Update the callback creation:
    cloudMT->setUpdateCallback(new CamPosUpdater(viewer, uCamPosOS.get()));

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
    viewer.setSceneData(createScene(&viewer));

    return viewer.run();
}