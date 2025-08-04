#include <WindowGL.h>

#include <iostream>

#include <imgui.h>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_glfw.h>

bool WindowGL::Init()
{
    if ( !glfwInit() )
    {
        std::cerr << "Error initializing GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 8);

    window_ = glfwCreateWindow(viewportWidth_, viewportHeight_, "Dear ImGui GLFW+OpenGL2", nullptr, nullptr);
    if (!window_)
    {
        std::cerr << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // Enable vsync

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
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL2_Init();

    SceneSetup();

    return true;
}

void WindowGL::SceneSetup()
{
    glViewport(0, 0, viewportWidth_, viewportHeight_);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double h2w = static_cast<double>(viewportHeight_) / static_cast<double>(viewportWidth_);
    //glFrustum(-1.0, 1.0, -1.0*h2w, 1.0*h2w, 1.0, 10.0);
    glOrtho(-1.0, 1.0, -1.0*h2w, 1.0*h2w, 1.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void WindowGL::Run()
{
    while ( !glfwWindowShouldClose(window_))
    {
        glfwPollEvents();
        if ( glfwGetWindowAttrib(window_, GLFW_ICONIFIED) != 0 )
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        constexpr ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_NoDockingInCentralNode
                                                     | ImGuiDockNodeFlags_PassthruCentralNode;
        auto dockspace_id = ImGui::GetID("MyDockSpace");
        dockspace_id = ImGui::DockSpaceOverViewport(dockspace_id, ImGui::GetMainViewport(), dockspace_flags);

        DrawScene();

        ImGui::Render();

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        // if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwMakeContextCurrent(window_);
        glfwSwapBuffers(window_);
    }

    glfwDestroyWindow(window_);
    glfwTerminate();
}

void WindowGL::DrawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    const float size = 0.5f;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-size, -size, 0.0f);
    glVertex3f(size, -size, 0.0f);
    glVertex3f(0.0f, size, 0.0f);
    glEnd();

    ImGui::Begin("Example Window");
    ImGui::Text("Hello, world!");
    ImGui::End();
}