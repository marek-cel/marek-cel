#include <SceneRoot.h>

#include <iostream>

#include <osg/Geode>
#include <osg/ShapeDrawable>

#include <QFile>
#include <QTextStream>

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

    createScene();
}

void SceneRoot::createScene()
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _root->addChild(geode.get());

    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3f(), 10.0, 10.0, 10.0);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(box.get());
    geode->addDrawable(shape.get());

    std::string vertCode = readShaderFromFile(":/shader.vert");
    std::string fragCode = readShaderFromFile(":/shader.frag");

    //std::cout << "shader.vert:\n" << vertCode;
    //std::cout << "shader.frag:\n" << fragCode;

    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode.c_str()));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode.c_str()));
    geode->getOrCreateStateSet()->setAttributeAndModes(program.get());
}

std::string SceneRoot::readShaderFromFile(const char* path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ts(&file);
    QString code = ts.readAll();
    return code.toStdString();
}
