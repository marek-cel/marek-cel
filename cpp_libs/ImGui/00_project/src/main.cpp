#include <iostream>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <cgi/SceneRoot.h>
#include <gui/ImGuiApp.h>

int main()
{
    std::cout << "Hello, World!" << std::endl;

    SceneRoot* sceneRoot = new SceneRoot();

    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
    viewer->setThreadingModel(viewer->SingleThreaded);
    viewer->setReleaseContextAtEndOfFrameHint(false);

    //viewer->setUpViewInWindow(400, 200, 1200, 800);
    viewer->setSceneData(sceneRoot->getRootNode());

    viewer->addEventHandler(new osgViewer::StatsHandler);

    viewer->getEventHandlers().push_front(new mc::gui::ImGuiApp);

    return viewer->run();
}