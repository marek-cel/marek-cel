#include <SceneRoot.h>

#include <iostream>

#include <osg/Geode>
#include <osg/ShapeDrawable>

#include <QFile>
#include <QTextStream>

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

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild( geode.get() );

    osg::ref_ptr<osg::Box> box = new osg::Box( osg::Vec3f(), 10.0f, 10.0f, 10.0f );

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( box.get() );
    geode->addDrawable( shape.get() );

    QFile fragFile( ":/shader.frag" );
    QFile vertFile( ":/shader.vert" );
    fragFile.open( QIODevice::ReadOnly | QIODevice::Text );
    vertFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QTextStream fragIn( &fragFile );
    QTextStream vertIn( &vertFile );
    QString fragCode = fragIn.readAll();
    QString vertCode = vertIn.readAll();

    std::cout << fragCode.toStdString() << std::endl;

    osg::ref_ptr<osg::Program> program = new osg::Program;
    //program->addShader( new osg::Shader( osg::Shader::VERTEX   , vertCode.toStdString().c_str() ) );
    program->addShader( new osg::Shader( osg::Shader::FRAGMENT , fragCode.toStdString().c_str() ) );
    geode->getOrCreateStateSet()->setAttributeAndModes( program.get() );
}

////////////////////////////////////////////////////////////////////////////////

SceneRoot::~SceneRoot() {}
