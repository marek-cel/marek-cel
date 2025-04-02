#include <SceneRoot.h>

#include <osg/BlendFunc>
#include <osg/ColorMask>
#include <osg/Depth>
#include <osg/Material>
#include <osgDB/ReadFile>

#include <TransparencyNode.h>

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
    osg::Node* loadedModel = osgDB::readNodeFile( "../../../OpenSceneGraph-Data-3.0.0/cessna.osgt" );

    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setAmbient( osg::Material::FRONT_AND_BACK, osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f) );
    material->setDiffuse( osg::Material::FRONT_AND_BACK, osg::Vec4(1.0f, 1.0f, 1.0f, 0.1f) );
    loadedModel->getOrCreateStateSet()->setAttributeAndModes(
        material.get(), osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE );
    loadedModel->getOrCreateStateSet()->setAttributeAndModes( new osg::BlendFunc );
    loadedModel->getOrCreateStateSet()->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );

    osg::ref_ptr<TransparencyNode> fxNode = new TransparencyNode;
    fxNode->addChild( loadedModel );

    _root->addChild( fxNode.get() );
}
