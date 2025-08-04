#include <iostream>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>

#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <KeyMap.h>
#include <SceneRoot.h>
#include <ImGuiApp.h>

double time_step = 0.016; // 60 FPS

GLFWwindow* window = nullptr;
int viewportWidth = 800;
int viewportHeight = 600;
bool isFullscreen = false;

ImGuiID dockspace_id = 0;

osg::ref_ptr<osgViewer::Viewer> viewer;
osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> gw;
osg::ref_ptr<osgGA::EventQueue> eq;
int mouseX = 0;
int mouseY = 0;

SceneRoot sceneRoot;

// struct PreDrawOp : public osg::Camera::DrawCallback
// {
//     void operator()(osg::RenderInfo& renderInfo) const override
//     {
//         ImGui_ImplOpenGL2_NewFrame();
//         ImGui_ImplGlfw_NewFrame();

//         ImGuiIO& io = ImGui::GetIO();

//         io.DisplaySize = ImVec2(renderInfo.getCurrentCamera()->getGraphicsContext()->getTraits()->width,
//                                 renderInfo.getCurrentCamera()->getGraphicsContext()->getTraits()->height);

//         ImGui::NewFrame();
//     }
// };

// struct PostDrawOp : public osg::Camera::DrawCallback
// {
//     void operator()(osg::RenderInfo& renderInfo) const override
//     {
//         osg::ref_ptr<osg::Camera> camera = renderInfo.getCurrentCamera();
//         osg::ref_ptr<osg::Viewport> viewport = camera->getViewport();


//         constexpr ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_NoDockingInCentralNode
//                                                      | ImGuiDockNodeFlags_PassthruCentralNode;
//         dockspace_id = ImGui::GetID("MyDockSpace");
//         dockspace_id = ImGui::DockSpaceOverViewport(dockspace_id, ImGui::GetMainViewport(), dockspace_flags);

//         ImGui::Begin("Example Window");
//         ImGui::Text("Hello, world!");
//         ImGui::End();

//         ImGui::Render();

//         ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

//         // ImGuiDockNode* central_node = ImGui::DockBuilderGetCentralNode(dockspace_id);
//         // auto io = ImGui::GetIO();
//         // if ( central_node )
//         // {
//         //     viewport->x() = central_node->Pos.x;
//         //     viewport->y() = io.DisplaySize.y - central_node->Size.y - central_node->Pos.y;
//         //     viewport->width() = central_node->Size.x;
//         //     viewport->height() = central_node->Size.y;
//         // }

//         // const osg::Matrixd& proj = camera->getProjectionMatrix();
//         // bool isOrtho = osg::equivalent(proj(3, 3), 1.0);
//         // if ( !isOrtho )
//         // {
//         //     double fovy, ar, znear, zfar;
//         //     camera->getProjectionMatrixAsPerspective(fovy, ar, znear, zfar);
//         //     camera->setProjectionMatrixAsPerspective(fovy, viewport->width() / viewport->height(), znear, zfar);
//         // }
//         // else
//         // {
//         //     double left, right, bottom, top, znear, zfar;
//         //     camera->getProjectionMatrixAsOrtho(left, right, bottom, top, znear, zfar);
//         //     camera->setProjectionMatrixAsOrtho(viewport->x(), viewport->x() + viewport->width(), viewport->y(), viewport->y() + viewport->height(), znear, zfar);
//         // }
//     }
// };

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << "Key pressed: " << (char)key << std::endl;

    if ( action == GLFW_PRESS )
    {
        eq->keyPress(convertKeyFromGlfwToOsg(key));

        if ( key == GLFW_KEY_F )
        {
            isFullscreen = !isFullscreen;
            if ( isFullscreen )
            {
                GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
                int monitorWidth = viewportWidth;
                int monitorHeight = viewportHeight;
                const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
                if ( mode )
                {
                    monitorWidth = mode->width;
                    monitorHeight = mode->height;
                }
                glfwSetWindowMonitor(window, primaryMonitor, 0, 0, monitorWidth, monitorHeight, GLFW_DONT_CARE);
            }
            else
            {
                glfwSetWindowMonitor(window, nullptr, 200, 100, viewportWidth, viewportHeight, GLFW_DONT_CARE);
            }
        }
    }
    else if ( action == GLFW_RELEASE )
    {
        eq->keyRelease(convertKeyFromGlfwToOsg(key));
    }

    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

void resize_callback(GLFWwindow* window, int width, int height)
{
    std::cout << "Window resized to: " << width << "x" << height << std::endl;
    eq->windowResize(0, 0, width, height);
    gw->resized(0, 0, width, height);
    if ( !isFullscreen )
    {
        viewportWidth = width;
        viewportHeight = height;
    }

    // ImGui_ImplGlfw_WindowSizeCallback(window, width, height);
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
    // std::cout << "Mouse moved to: " << xpos << ", " << ypos << std::endl;
    mouseX = static_cast<int>(xpos);
    mouseY = static_cast<int>(ypos);
    eq->mouseMotion(mouseX, mouseY);

    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if ( action == GLFW_PRESS )
    {
        std::cout << "Mouse button pressed: " << button << " at (" << mouseX << ", " << mouseY << ")" << std::endl;
        eq->mouseButtonPress(mouseX, mouseY, button);
    }
    else if ( action == GLFW_RELEASE )
    {
        std::cout << "Mouse button released: " << button << " at (" << mouseX << ", " << mouseY << ")" << std::endl;
        eq->mouseButtonRelease(mouseX, mouseY, button);
    }

    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << "Mouse scrolled: " << xoffset << ", " << yoffset << std::endl;
    osgGA::GUIEventAdapter::ScrollingMotion sm;
    if ( yoffset > 0 )
        sm = osgGA::GUIEventAdapter::SCROLL_UP;
    else if ( yoffset < 0 )
        sm = osgGA::GUIEventAdapter::SCROLL_DOWN;
    else
        sm = osgGA::GUIEventAdapter::SCROLL_NONE;

    eq->mouseScroll(sm, time_step);

    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

void init()
{
    if ( !glfwInit() )
    {
        std::cerr << "Error initializing GLFW" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 8);

    window = glfwCreateWindow(viewportWidth, viewportHeight, "Dear ImGui GLFW+OpenGL2", nullptr, nullptr);
    if ( !window )
    {
        std::cerr << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    glfwSetWindowPos(window, 200, 100);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, false);
    ImGui_ImplOpenGL2_Init();

    // Setup OSG viewer
	viewer = new osgViewer::Viewer;
    gw = viewer->setUpViewerAsEmbeddedInWindow(0, 0, viewportWidth, viewportHeight);
    eq = gw->getEventQueue();

    viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
    viewer->setKeyEventSetsDone(0); // prevent viewer from closing when pressing ESC
    viewer->setReleaseContextAtEndOfFrameHint(false);
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
    // camera->setPreDrawCallback(new PreDrawOp);
    // camera->setPostDrawCallback(new PostDrawOp);

    if ( !viewer->isRealized() )
    {
        viewer->realize();
    }

    viewer->setSceneData(sceneRoot.getRootNode());

    // Set GLFW callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, resize_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);
}

int main(int argc, char* argv[])
{
    init();

    while ( true )
    {
        time_step = 0.016; // TODO: Calculate time step based on actual frame time

        if ( glfwWindowShouldClose(window) )
        {
            glfwSetWindowShouldClose(window, GLFW_FALSE);
            std::cout << "GLFW window closed" << std::endl;
            break;
        }

        glfwPollEvents();


        if ( glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0 )
        {
            ImGui_ImplGlfw_Sleep(16);
            continue;
        }

        viewer->frame();



        ImGuiIO& io = ImGui::GetIO();
        if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
