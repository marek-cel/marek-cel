/**
 * Basic volumetric cloud example.
 *
 * The program creates a single simplified static cumulus humilis cloud.
 * This program is intended to be used in real time rendering applications on
 * a relatively low spec hardware (integrated graphics).
 */

#include <fstream>
#include <iostream>
#include <random>
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

uniform vec3 uCamPosOS;     // camera position in *object* space
uniform vec3 uCloudOffset;  // per-cloud random offset for noise variation
uniform float uDensity;     // overall density multiplier
uniform int uSteps;         // march steps (e.g., 12–16)
uniform float uStepMul;     // step length multiplier (e.g., 1.0/float(uSteps))
uniform vec3 uLightDirOS;   // normalized light dir in object space (to light)
uniform vec3 uLightColor;   // light color
uniform int uShadowSteps;   // shadow-ray steps (e.g., 4–8)
uniform float uBaseZ;       // cloud base z-coordinate
uniform float uBaseSoft;    // softness (thickness of the base transition), e.g. 0.06
uniform float uBaseWarpAmp; // amplitude of base waviness, e.g. 0.02

// GLSL 1.20 — 3D Perlin (gradient) noise, returns [-1, 1]
float fade(float t) { return t*t*t*(t*(t*6.0 - 15.0) + 10.0); }

// Hash -> pseudo-random unit-ish gradient per integer lattice point
vec3 grad3(vec3 i)
{
    // independent hashes for x,y,z components
    vec3 s = vec3(
        dot(i, vec3(127.1, 311.7,  74.7)),
        dot(i, vec3(269.5, 183.3, 246.1)),
        dot(i, vec3(113.5, 271.9, 124.6))
    );
    vec3 g = fract(sin(s) * 43758.5453) * 2.0 - 1.0;
    // normalize to unit length (approx)
    return g * inversesqrt(dot(g, g) + 1e-6);
}

float perlinNoise(vec3 P)
{
    vec3 Pi = floor(P);
    vec3 Pf = P - Pi;

    // Corner offsets
    vec3 c000 = vec3(0.0, 0.0, 0.0);
    vec3 c100 = vec3(1.0, 0.0, 0.0);
    vec3 c010 = vec3(0.0, 1.0, 0.0);
    vec3 c110 = vec3(1.0, 1.0, 0.0);
    vec3 c001 = vec3(0.0, 0.0, 1.0);
    vec3 c101 = vec3(1.0, 0.0, 1.0);
    vec3 c011 = vec3(0.0, 1.0, 1.0);
    vec3 c111 = vec3(1.0, 1.0, 1.0);

    // Gradients at cube corners (hashed by lattice coords)
    vec3 g000 = grad3(Pi + c000);
    vec3 g100 = grad3(Pi + c100);
    vec3 g010 = grad3(Pi + c010);
    vec3 g110 = grad3(Pi + c110);
    vec3 g001 = grad3(Pi + c001);
    vec3 g101 = grad3(Pi + c101);
    vec3 g011 = grad3(Pi + c011);
    vec3 g111 = grad3(Pi + c111);

    // Dot with displacement to corners
    float n000 = dot(g000, Pf - c000);
    float n100 = dot(g100, Pf - c100);
    float n010 = dot(g010, Pf - c010);
    float n110 = dot(g110, Pf - c110);
    float n001 = dot(g001, Pf - c001);
    float n101 = dot(g101, Pf - c101);
    float n011 = dot(g011, Pf - c011);
    float n111 = dot(g111, Pf - c111);

    // Quintic fade and trilinear interpolation
    vec3 u = vec3(fade(Pf.x), fade(Pf.y), fade(Pf.z));

    float nx00 = mix(n000, n100, u.x);
    float nx10 = mix(n010, n110, u.x);
    float nx01 = mix(n001, n101, u.x);
    float nx11 = mix(n011, n111, u.x);

    float nxy0 = mix(nx00, nx10, u.y);
    float nxy1 = mix(nx01, nx11, u.y);

    //return mix(nxy0, nxy1, u.z); // in [-1, 1]
    return (mix(nxy0, nxy1, u.z) + 0.5) * 0.5;
}

// Fractional Brownian Motion (fBm) for more complex noise
float fbm(vec3 p) {
    float value = 0.0;
    float amplitude = 0.5;
    float frequency = 1.0;

    for (int i = 0; i < 4; i++) {
        // apply cloud offset to each octave to avoid identical repetition
        value += amplitude * perlinNoise((p + uCloudOffset * 0.002) * frequency);
        amplitude *= 0.5;
        frequency *= 2.0;
    }
    return value;
}

// Cloud density function
float cloudDensity(vec3 p) {
    // Stay inside the unit sphere
    float dist = length(p);
    if (dist > 1.0) return 0.0;

    // ---- soft flat base (Z is up) ----
    // tiny horizontal warp so it isn't a perfect plane
    // include per-cloud offset in the base warp sampling
    float baseWarp = (fbm(vec3((p.xz + uCloudOffset.xz) * 1.2, 0.0)) - 0.5) * 2.0 * uBaseWarpAmp;
    float baseZ = uBaseZ + baseWarp;

    // humidity ramp across the lifting condensation level
    // 0 below, ~1 above, with softness controlled by uBaseSoft
    float humid = smoothstep(baseZ - uBaseSoft, baseZ + uBaseSoft, p.z);
    if (humid <= 0.0) return 0.0; // quick exit

    // soft spherical falloff for top/sides
    float sphereFalloff = 1.0 - smoothstep(0.6, 1.0, dist);

    // normalized height above the (warped) base
    float h = clamp((p.z - baseZ) / (1.0 - baseZ), 0.0, 1.0);

    // silhouette (low freq) and detail (high freq); more detail higher up
    vec3 q = p * 2.0;
    // offset high/low frequency sampling to break symmetry between clouds
    float low  = fbm(q * 0.8 + uCloudOffset * 0.3);
    float high = fbm(q * 3.0 + uCloudOffset * 0.6);
    float n = mix(low, high, h * h);

    // billowy lobes
    n = 1.0 - abs(2.0 * n - 1.0);

    // combine pieces
    float d = sphereFalloff * n;

    // keep underside cleaner; fuller higher up
    d *= mix(0.6, 1.0, h);

    // apply humidity ramp (soft base)
    d *= humid;

    // softer threshold to open gaps without hard cutting
    d = smoothstep(0.18, 0.45, d);

    return d;
}

// Calculate shadow attenuation by marching toward the light
float calculateShadow(vec3 pos, vec3 lightDir, float shadowStepSize) {
    float shadowDensity = 0.0;

    // March toward the light
    for (int i = 0; i < 32; ++i) { // static upper bound for GLSL 1.20
        if (i >= uShadowSteps) break;

        vec3 shadowPos = pos + lightDir * shadowStepSize * float(i + 1);

        // Check if we're still inside the unit sphere (our cloud bounds)
        if (length(shadowPos) > 1.0) break;

        float density = cloudDensity(shadowPos);
        shadowDensity += 5.0 * density * shadowStepSize;

        // Early exit if we've accumulated enough shadow
        if (shadowDensity > 3.0) break;
    }

    // Convert accumulated density to shadow attenuation
    // Higher shadowDensity = more shadowed = lower attenuation
    return exp(-shadowDensity * 2.0); // Exponential falloff for realistic shadowing
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

    // Calculate shadow step size (should be larger than primary ray step for performance)
    float shadowStepSize = dt * 2.0;

    vec3 col = vec3(0.9, 0.95, 1.0); // slightly blue-tinted base color (sky influence)
    float alpha = 0.0;

    // Front-to-back alpha compositing with noise-based density and self-shadowing
    for (int i = 0; i < 64; ++i) // static upper bound for GLSL 1.20
    {
        if (i >= uSteps) break;

        vec3 p = ro + rd * (t + dt * float(i));

        float density = cloudDensity(p) * uDensity;
        if (density <= 0.0) continue; // Skip empty space

        // Calculate lighting with self-shadowing
        float shadowAttenuation = calculateShadow(p, uLightDirOS, shadowStepSize);

        // Apply lighting: base ambient + directional light with shadows
        float ambient = 0.3; // Some ambient lighting so shadows aren't completely black
        float lighting = ambient + (1.0 - ambient) * shadowAttenuation;

        // Color the cloud based on lighting
        vec3 cloudColor = uLightColor * lighting;

        float a = 1.0 - exp(-density * dt * 8.0); // Beer-Lambert absorption

        // Front-to-back compositing
        col = mix(col, cloudColor, a * (1.0 - alpha));
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

struct CloudData
{
    osg::Vec3 center;
    float size_x;
    float size_y;
    float size_z;
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

    CloudData data;
    std::vector<CloudData> clouds;

    data.center = osg::Vec3(0.0f, 0.0f, 1.5f);
    data.size_x = 150.0f;
    data.size_y = 250.0f;
    data.size_z = 160.0f;
    clouds.push_back(data);

    data.center = osg::Vec3(200.0f, 300.0f, 0.0f);
    data.size_x = 150.0f;
    data.size_y = 150.0f;
    data.size_z = 80.0f;
    clouds.push_back(data);

    data.center = osg::Vec3(-200.0f, 300.0f, 0.0f);
    data.size_x = 150.0f;
    data.size_y = 250.0f;
    data.size_z = 120.0f;
    clouds.push_back(data);

    for ( auto cloud : clouds )
    {
        // --- Cloud proxy: cube enclosing a unit sphere ---
        osg::ref_ptr<osg::Geode> cloudGeode = new osg::Geode();
        osg::ref_ptr<osg::ShapeDrawable> cloudCube =
            new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.f, 0.f, 0.f), 2.f));
        // size=2 → unit radius sphere fits inside cube (-1..1)

        cloudGeode->addDrawable(cloudCube.get());

        // Place & scale the cloud node in world (adjust to your liking)
        osg::Matrix cloudXform = osg::Matrix::scale(osg::Vec3(cloud.size_x, cloud.size_y, cloud.size_z)) *  // non-uniform later
                                osg::Matrix::translate(cloud.center);
        osg::ref_ptr<osg::MatrixTransform> cloudMT = new osg::MatrixTransform(cloudXform);
        cloudMT->addChild(cloudGeode.get());
        root->addChild(cloudMT.get());

        osg::Matrixd localToWorld = cloudMT->getMatrix();
        osg::Matrixd worldToLocal = osg::Matrixd::inverse(localToWorld);

        osg::Vec3d lightObj = lightPosition * worldToLocal;   // into cloud's object space
        osg::Vec3  lightDir = osg::Vec3(lightObj) - osg::Vec3(0,0,0);
        lightDir.normalize();

        // debug wireframe
        root->addChild(createBoxWireframe(cloud.center, cloud.size_x, cloud.size_y, cloud.size_z));

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
        depth->setWriteMask(false); // don't write depth (we're translucent)
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
        osg::ref_ptr<osg::Uniform> uBaseZ       = new osg::Uniform("uBaseZ", -0.00f); // as before
        osg::ref_ptr<osg::Uniform> uBaseSoft    = new osg::Uniform("uBaseSoft", 0.06f);
        osg::ref_ptr<osg::Uniform> uBaseWarpAmp = new osg::Uniform("uBaseWarpAmp", 0.02f);

        // per-cloud random offset to make each cloud unique
        static std::mt19937 rng(time(nullptr));
        static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
        osg::Vec3 cloudOffset(dist(rng), dist(rng), dist(rng));
        osg::ref_ptr<osg::Uniform> uCloudOffset = new osg::Uniform("uCloudOffset", cloudOffset);

        cloudStateSet->addUniform(uCamPosOS.get());
        cloudStateSet->addUniform(uDensity.get());
        cloudStateSet->addUniform(uSteps.get());
        cloudStateSet->addUniform(uStepMul.get());
        cloudStateSet->addUniform(uLightDirOS.get());
        cloudStateSet->addUniform(uLightColor.get());
        cloudStateSet->addUniform(uShadowSteps.get());
        cloudStateSet->addUniform(uBaseZ.get());
        cloudStateSet->addUniform(uBaseSoft.get());
        cloudStateSet->addUniform(uBaseWarpAmp.get());
    cloudStateSet->addUniform(uCloudOffset.get());

        // Update the callback creation:
        cloudMT->setUpdateCallback(new CamPosUpdater(viewer, uCamPosOS.get()));
    }

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