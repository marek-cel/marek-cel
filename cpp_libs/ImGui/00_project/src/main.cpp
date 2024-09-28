#include <iostream>

#include <osgViewer/Viewer>

#include <cgi/SceneRoot.h>
#include <gui/ImGuiApp.h>

int main()
{
    std::cout << "Hello, World!" << std::endl;

    SceneRoot* sceneRoot = new SceneRoot();

    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

    viewer->setUpViewInWindow(400, 200, 1200, 800);
    viewer->setSceneData(sceneRoot->getRootNode());

    viewer->setRealizeOperation(new mc::gui::ImGuiRealizeOperation);
    viewer->getEventHandlers().push_front(new mc::gui::ImGuiApp);

    return viewer->run();
}