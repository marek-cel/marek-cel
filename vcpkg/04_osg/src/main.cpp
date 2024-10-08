#include <iostream>

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

int main()
{
	std::cout << "Hello, World!" << std::endl;

    osgViewer::Viewer viewer;

	viewer.setCameraManipulator(new osgGA::TrackballManipulator);
	viewer.addEventHandler(new osgViewer::StatsHandler);

    osg::ref_ptr<osg::Group> sceneRoot = new osg::Group;

    osg::ref_ptr<osg::StateSet> stateSet = sceneRoot->getOrCreateStateSet();
    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    sceneRoot->addChild(geode.get());

    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3f(), 10.0, 10.0, 10.0);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(box.get());
    geode->addDrawable(shape.get());

    viewer.setUpViewInWindow(400, 200, 800, 600);
    viewer.setSceneData(sceneRoot.get());

    return viewer.run();
}