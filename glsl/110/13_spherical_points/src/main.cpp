#include <fstream>
#include <iostream>
#include <sstream>

#include <osg/ArgumentParser>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>

// Vertex Shader
const char* vertCode = R"(
#version 120

uniform float sphereRadius;
varying vec3 worldPos;
varying vec3 eyePos;
varying vec4 color;

void main()
{
    // Transform vertex to world space
    worldPos = (gl_ModelViewMatrix * gl_Vertex).xyz;

    // Eye position in view space
    eyePos = worldPos;

    // Calculate distance from camera to point
    float distance = length(eyePos);

    // Set point size based on distance and desired sphere radius
    // This creates perspective scaling - closer spheres appear larger
    gl_PointSize = max(1.0, (sphereRadius * 100.0) / distance);

    // Pass through color
    color = gl_Color;

    // Standard vertex transformation
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
)";

// Fragment Shader
const char* fragCode = R"(
#version 120

uniform float sphereRadius;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec4 ambientLight;

varying vec3 worldPos;
varying vec3 eyePos;
varying vec4 color;

void main()
{
    // Get point coordinate within the point sprite (0-1, 0-1)
    vec2 coord = gl_PointCoord.xy;

    // Convert to centered coordinates (-1 to 1)
    vec2 centered = coord * 2.0 - 1.0;

    // Calculate distance from center
    float dist = length(centered);

    // Discard fragments outside the circle (creates circular points)
    if (dist > 1.0) {
        discard;
    }

    // Calculate the Z coordinate on the sphere surface
    // This creates the 3D sphere illusion
    float z = sqrt(1.0 - dist * dist);

    // Calculate the normal vector for lighting
    vec3 normal = normalize(vec3(centered.x, centered.y, z));

    // Transform normal to world space (approximate)
    // For more accuracy, you'd want to pass proper matrices
    vec3 worldNormal = normal;

    // Calculate lighting
    vec3 lightDir = normalize(lightPosition - worldPos);

    // Diffuse lighting
    float diffuse = max(0.0, dot(worldNormal, lightDir));

    // Simple specular highlight
    vec3 viewDir = normalize(-eyePos);
    vec3 reflectDir = reflect(-lightDir, worldNormal);
    float specular = pow(max(0.0, dot(viewDir, reflectDir)), 32.0);

    // Combine lighting components
    vec4 finalColor = color * ambientLight +
                     color * lightColor * diffuse +
                     lightColor * specular * 0.3;

    // Add some depth-based shading for better 3D effect
    float depthShading = 0.8 + 0.2 * z;
    finalColor.rgb *= depthShading;

    gl_FragColor = finalColor;
}
)";

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

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
    geode->addDrawable(geom.get());

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();  // vertices
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();  // colors

    // Create a more interesting pattern of points
    for ( uint32_t i = 0; i < 10; ++i )
    {
        v->push_back(osg::Vec3(i * 0.5f, 0.0f, 0.0f));  // water points spread out
        c->push_back(osg::Vec4(0.3f, 0.7f, 1.0f, 1.0f));  // blue color for each point
    }

    geom->setVertexArray(v.get());
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, v->size()));
    geom->setColorArray(c.get());
    geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    osg::ref_ptr<osg::StateSet> geodeStateSet = geode->getOrCreateStateSet();

    // Enable point sprites
    geodeStateSet->setMode(GL_POINT_SPRITE, osg::StateAttribute::ON);
    geodeStateSet->setMode(GL_VERTEX_PROGRAM_POINT_SIZE, osg::StateAttribute::ON);

    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode));
    geodeStateSet->setAttributeAndModes(program.get());

    // Add shader uniforms
    geodeStateSet->addUniform(new osg::Uniform("sphereRadius", 3.0f)); // Radius in scene units
    geodeStateSet->addUniform(new osg::Uniform("lightPosition", osg::Vec3(6.0f, -2.0f, 4.0f)));
    geodeStateSet->addUniform(new osg::Uniform("lightColor", osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    geodeStateSet->addUniform(new osg::Uniform("ambientLight", osg::Vec4(0.2f, 0.2f, 0.3f, 1.0f)));

    return root.release();
}

int main(int argc, char* argv[])
{
    osg::ArgumentParser arguments(&argc, argv);
    osgViewer::Viewer viewer(arguments);

    viewer.setCameraManipulator(new osgGA::TrackballManipulator());
    viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
    viewer.addEventHandler(new osgViewer::StatsHandler());
    viewer.setUpViewInWindow(0, 0, 800, 600);
    viewer.setSceneData(createScene());

    return viewer.run();
}