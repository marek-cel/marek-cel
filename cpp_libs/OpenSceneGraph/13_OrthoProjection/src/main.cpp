#include <iostream>

#include <osg/Geode>
#include <osg/ShapeDrawable>

#include <osgGA/StateSetManipulator>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

constexpr double fov_y = 50.0;
constexpr double fov_y_2 = fov_y / 2.0;

// TODO: implement a custom ortho projection camera manipulator class


void setupEventHandlers(osgViewer::Viewer* viewer)
{
    // add the state manipulator
    viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

    // add the thread model handler
    viewer->addEventHandler(new osgViewer::ThreadingHandler);

    // add the window size toggle handler
    viewer->addEventHandler(new osgViewer::WindowSizeHandler);

    // add the stats handler
    viewer->addEventHandler(new osgViewer::StatsHandler);

    // TODO: set the ortho projection camera manipulator
}

void setupCamera(osgViewer::Viewer* viewer)
{
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
    if ( camera.valid() == false )
    {
        std::cerr << "Error: Camera is invalid." << std::endl;
        return;
    }

    osg::GraphicsContext* context = camera->getGraphicsContext();
    if ( context == nullptr )
    {
        std::cerr << "Error: GraphicsContext is null." << std::endl;
        return;
    }

    const osg::GraphicsContext::Traits* traits = camera->getGraphicsContext()->getTraits();

    double w2h = static_cast<double>(traits->width)
               / static_cast<double>(traits->height);

    camera->setProjectionMatrixAsOrtho(-fov_y_2 * w2h, fov_y_2 * w2h, -fov_y_2, fov_y_2, 0.1, 1000000.0);
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

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    root->addChild(geode.get());

    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3f(), 10.0, 10.0, 10.0);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(box.get());
    geode->addDrawable(shape.get());

    return root.release();
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    osgViewer::Viewer viewer;
    
    setupEventHandlers(&viewer);
    

    viewer.setUpViewInWindow(400, 200, 800, 600);
    viewer.setSceneData(createScene());

    setupCamera(&viewer);

    return viewer.run();
}
