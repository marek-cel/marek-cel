#include <cstdio>
#include <cstring>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

int main(int argc, char* argv[])
{
    if (!glfwInit())
    {
        std::cerr << "Error initializing GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL - GLFW", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    std::cout << "" << std::endl;
    std::cout << "" << "OpenGL Vendor: "   << glGetString(GL_VENDOR)   << std::endl;
    std::cout << "" << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "" << "OpenGL Version: "  << glGetString(GL_VERSION)  << std::endl;
    std::cout << "" << "OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "" << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}