#include <WindowGL.h>

#include <iostream>

bool WindowGL::Init()
{
    if (!glfwInit())
    {
        std::cerr << "Error initializing GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    window_ = glfwCreateWindow(viewportWidth_, viewportHeight_, "OpenGL - GLFW", nullptr, nullptr);
    if (!window_)
    {
        std::cerr << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window_);

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

void WindowGL::PrintInfo()
{
    std::cout << "" << std::endl;
    std::cout << "" << "OpenGL Vendor: "   << glGetString(GL_VENDOR)   << std::endl;
    std::cout << "" << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "" << "OpenGL Version: "  << glGetString(GL_VERSION)  << std::endl;
    std::cout << "" << "OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "" << std::endl;
}

void WindowGL::Run()
{
    while (!glfwWindowShouldClose(window_))
    {
        DrawScene();
        glfwSwapBuffers(window_);
        glfwPollEvents();
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
}