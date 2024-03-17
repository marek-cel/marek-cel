#include <SceneRoot.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include <osg/Geode>
#include <osg/ShapeDrawable>

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

    std::string vertCode = readShaderFromFile("../shaders/shader.vert");
    std::string fragCode = readShaderFromFile("../shaders/shader.frag");

    //std::cout << "shader.vert:\n" << vertCode;
    //std::cout << "shader.frag:\n" << fragCode;

    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader(new osg::Shader(osg::Shader::VERTEX   , vertCode.c_str()));
    program->addShader(new osg::Shader(osg::Shader::FRAGMENT , fragCode.c_str()));
    geode->getOrCreateStateSet()->setAttributeAndModes(program.get());
}

std::string SceneRoot::readShaderFromFile(const char* path)
{
    std::string result;

    std::ifstream ifs(path, std::ifstream::in);
    if ( ifs.is_open() )
    {
        std::string line;
        while ( getline(ifs, line) )
        {
            result += line + "\n";
        }
        ifs.close();
    }
    else
    {
        std::cerr << "Cannot open file: " << path << std::endl;
    }

    return result;
}
