#include <iostream>

#include <osg/ArgumentParser>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/SphericalManipulator>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <SceneRoot.h>
#include <OsgImGuiHandler.hpp>

class ImGuiInitOperation : public osg::Operation
{
public:
    ImGuiInitOperation()
        : osg::Operation("ImGuiInitOperation", false)
    {
    }

    void operator()(osg::Object* object) override
    {
        osg::GraphicsContext* context = dynamic_cast<osg::GraphicsContext*>(object);
        if (!context)
            return;

        if (!ImGui_ImplOpenGL3_Init())
        {
            std::cout << "ImGui_ImplOpenGL3_Init() failed\n";
        }
    }
};

class ImGuiDemo : public OsgImGuiHandler
{
protected:
    void drawUi() override
    {
        // ImGui code goes here...
        ImGui::ShowDemoWindow();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", "CTRL+N")) {}
                if (ImGui::MenuItem("Open", "CTRL+N")) {}
                if (ImGui::MenuItem("Exit", "CTRL+N")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
};

void setupCameraManipulators(osgViewer::Viewer* viewer, osg::ArgumentParser* arguments);
void setupEventHandlers(osgViewer::Viewer* viewer, osg::ArgumentParser* arguments);

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

//#   ifdef _LINUX_
//    setenv("LC_NUMERIC", "en_US", 1);
//#   endif

    osg::ArgumentParser arguments(&argc, argv);

    osgViewer::Viewer viewer(arguments);

    setupCameraManipulators(&viewer, &arguments);
    setupEventHandlers(&viewer, &arguments);

    SceneRoot sceneRoot;

    viewer.setUpViewInWindow(400, 200, 1200, 800);
    viewer.setSceneData(sceneRoot.getNode());

    viewer.setRealizeOperation(new ImGuiInitOperation);
    viewer.addEventHandler(new ImGuiDemo);

    osg::GraphicsContext* context = viewer.getCamera()->getGraphicsContext();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits(*context->getTraits());
    traits->windowName = "ImGui Example";
    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
    viewer.getCamera()->setGraphicsContext(gc);

    return viewer.run();
}

void setupCameraManipulators(osgViewer::Viewer *viewer, osg::ArgumentParser *arguments)
{
    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManip = new osgGA::KeySwitchMatrixManipulator();

    keyswitchManip->addMatrixManipulator( '1', "Trackball"   , new osgGA::TrackballManipulator()   );
    keyswitchManip->addMatrixManipulator( '2', "Flight"      , new osgGA::FlightManipulator()      );
    keyswitchManip->addMatrixManipulator( '3', "Drive"       , new osgGA::DriveManipulator()       );
    keyswitchManip->addMatrixManipulator( '4', "Terrain"     , new osgGA::TerrainManipulator()     );
    keyswitchManip->addMatrixManipulator( '5', "Orbit"       , new osgGA::OrbitManipulator()       );
    keyswitchManip->addMatrixManipulator( '6', "FirstPerson" , new osgGA::FirstPersonManipulator() );
    keyswitchManip->addMatrixManipulator( '7', "Spherical"   , new osgGA::SphericalManipulator()   );

    std::string pathfile;
    double animationSpeed = 1.0;
    while(arguments->read("--speed",animationSpeed) ) {}
    char keyForAnimationPath = '8';
    while (arguments->read("-p",pathfile))
    {
        osgGA::AnimationPathManipulator* apm = new osgGA::AnimationPathManipulator(pathfile);
        if (apm || !apm->valid())
        {
            apm->setTimeScale(animationSpeed);

            unsigned int num = keyswitchManip->getNumMatrixManipulators();
            keyswitchManip->addMatrixManipulator(keyForAnimationPath, "Path", apm);
            keyswitchManip->selectMatrixManipulator(num);
            ++keyForAnimationPath;
        }
    }

    viewer->setCameraManipulator(keyswitchManip.get());
}

void setupEventHandlers(osgViewer::Viewer* viewer, osg::ArgumentParser* arguments)
{
    // add the state manipulator
    viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

    // add the thread model handler
    viewer->addEventHandler(new osgViewer::ThreadingHandler);

    // add the window size toggle handler
    viewer->addEventHandler(new osgViewer::WindowSizeHandler);

    // add the stats handler
    viewer->addEventHandler(new osgViewer::StatsHandler);

    // add the help handler
    viewer->addEventHandler(new osgViewer::HelpHandler(arguments->getApplicationUsage()));

    // add the record camera path handler
    viewer->addEventHandler(new osgViewer::RecordCameraPathHandler);

    // add the LOD Scale handler
    viewer->addEventHandler(new osgViewer::LODScaleHandler);

    // add the screen capture handler
    viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
}
