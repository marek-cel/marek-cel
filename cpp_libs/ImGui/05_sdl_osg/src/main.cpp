#include <filesystem>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <SDL.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <remapKeysFromSdlToOsg.h>

#include <cgi/SceneRoot.h>
#include <gui/ImGuiApp.h>

const bool multi_viewports = false;
bool is_running = true;

double time_step = 0.0;
double time_prev = 0.0;

const char* settings_file = "project.json";
boost::property_tree::ptree pt;

SDL_Window* window = nullptr;
SDL_GLContext gl_context;
SDL_Renderer* renderer = nullptr;

osg::ref_ptr<osgViewer::Viewer> viewer;
osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> gw;
osg::ref_ptr<osgGA::EventQueue> eq;

void initCfg()
{
    // Check if the config file exists. If not, create an empty one.
    if ( !std::filesystem::exists(settings_file) )
    {
        boost::property_tree::ptree temp;
        try
        {
            boost::property_tree::write_json(settings_file, temp);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error creating config file: " << e.what() << std::endl;
            exit(1);
        }
    }

    try
    {
        boost::property_tree::read_json(settings_file, pt);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error reading config file: " << e.what() << std::endl;
        exit(1);
    }
}

void saveCfg()
{
    int pos_x;
    int pos_y;
    SDL_GetWindowPosition(window, &pos_x, &pos_y);
    pt.put("main_window.pos_x", pos_x);
    pt.put("main_window.pos_y", pos_y);

    int width;
    int height;
    SDL_GetWindowSize(window, &width, &height);
    pt.put("main_window.width"  , width);
    pt.put("main_window.height" , height);
    boost::property_tree::write_json(settings_file, pt);
}

void initSDL()
{
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
	}

    if ( multi_viewports )
    {
        SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
    }

    int pos_x  = pt.get<int>("main_window.pos_x"  , SDL_WINDOWPOS_CENTERED);
    int pos_y  = pt.get<int>("main_window.pos_y"  , SDL_WINDOWPOS_CENTERED);
    int width  = pt.get<int>("main_window.width"  , 800);
    int height = pt.get<int>("main_window.height" , 600);
    Uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow("ImGui - SDL - OSG", pos_x, pos_y, width, height, window_flags);
    if ( !window )
    {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        exit(1);
    }

    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(window, -1, renderer_flags);
    if ( !renderer )
    {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void initGUI()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavNoCaptureKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		// Enable Docking
    if ( multi_viewports )
    {
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    }
    io.IniFilename = "project.ini";

    // initFonts();
    // initStyle();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    // ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplOpenGL3_Init();
}

void initOSG()
{
    int width;
    int height;
    SDL_GetWindowSize(window, &width, &height);
    viewer = new osgViewer::Viewer();
    gw = viewer->setUpViewerAsEmbeddedInWindow(0, 0, width, height);
    eq = gw->getEventQueue();

    SceneRoot cgi;

    viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
    viewer->setKeyEventSetsDone(0); // prevent viewer from closing when pressing ESC
    viewer->setReleaseContextAtEndOfFrameHint(false);
    viewer->setSceneData(cgi.getRootNode());
    viewer->setCameraManipulator(new osgGA::TrackballManipulator());
    viewer->addEventHandler(new osgViewer::StatsHandler);
    osg::ref_ptr<ImGuiApp> imgui_app = new ImGuiApp();
    viewer->getEventHandlers().push_front(imgui_app);

    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
    const osg::GraphicsContext::Traits* traits = camera->getGraphicsContext()->getTraits();
    double w2h = static_cast<double>(traits->width) / static_cast<double>(traits->height);
    // camera->setClearColor(osg::Vec4(0.0, 0.0, 0.0, 1.0));
    camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    const double z_near = 1.0;
    const double z_far = 1.0e5;
    camera->setProjectionMatrixAsPerspective(40, w2h, z_near, z_far);
    camera->setNearFarRatio(z_near / z_far);

    if ( !viewer->isRealized() )
    {
        viewer->realize();
    }
}

void handleEvents()
{
    SDL_Event e;
    while ( SDL_PollEvent(&e) )
    {
        ImGui_ImplSDL2_ProcessEvent(&e);

        if ( !ImGui::GetIO().WantCaptureMouse && !ImGui::GetIO().WantCaptureKeyboard )
        {
            switch (e.type)
            {
            case SDL_MOUSEMOTION:
                eq->mouseMotion(e.motion.x, e.motion.y);
                break;

            case SDL_MOUSEBUTTONDOWN:
                eq->mouseButtonPress(e.button.x, e.button.y, e.button.button);
                break;

            case SDL_MOUSEBUTTONUP:
                eq->mouseButtonRelease(e.button.x, e.button.y, e.button.button);
                break;

            case SDL_MOUSEWHEEL:
                osgGA::GUIEventAdapter::ScrollingMotion sm;
                if ( e.wheel.direction == SDL_MOUSEWHEEL_NORMAL )
                {
                    if ( e.wheel.preciseY > 0.0 )
                    {
                        sm = osgGA::GUIEventAdapter::SCROLL_UP;
                    }
                    else
                    {
                        sm = osgGA::GUIEventAdapter::SCROLL_DOWN;
                    }
                }
                else
                {
                    if ( e.wheel.preciseY > 0.0 )
                    {
                        sm = osgGA::GUIEventAdapter::SCROLL_DOWN;
                    }
                    else
                    {
                        sm = osgGA::GUIEventAdapter::SCROLL_UP;
                    }
                }
                eq->mouseScroll(sm, time_step);
                break;

            case SDL_KEYDOWN:
                eq->keyPress(remapKeysFromSdlToOsg(e.key.keysym));
                break;

            case SDL_KEYUP:
                eq->keyRelease(remapKeysFromSdlToOsg(e.key.keysym));
                break;
            }
        }

        switch (e.type)
        {
        case SDL_WINDOWEVENT:
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                eq->windowResize(0, 0, e.window.data1, e.window.data2);
                gw->resized(0, 0, e.window.data1, e.window.data2);
                break;
            }

            break;

        case SDL_QUIT:
            is_running = false;
            break;
        }
    }
}

int main()
{
    initCfg();
    initSDL();
    initGUI();
    initOSG();

    time_prev = SDL_GetTicks() / 1000.0;

    while( is_running )
    {
        double now = SDL_GetTicks() / 1000.0;
        time_step = now - time_prev;
        time_prev = now;

        handleEvents();

        viewer->frame();

        if ( multi_viewports )
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        SDL_GL_SwapWindow(window);
    }

    saveCfg();

    return 0;
}
