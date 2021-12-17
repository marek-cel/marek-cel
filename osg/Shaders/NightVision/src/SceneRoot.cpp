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

    osg::ref_ptr<osg::Box> box = new osg::Box( osg::Vec3f(), 1.0f, 1.0f, 1.0f );
    osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere( osg::Vec3f(), 1.0f );

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( box.get() );
    geode->addDrawable( shape.get() );

    osg::ref_ptr<osg::Program> program = new osg::Program();
    program->addShader( new osg::Shader( osg::Shader::VERTEX   , shader_vert ) );
    program->addShader( new osg::Shader( osg::Shader::FRAGMENT , shader_frag ) );
}
