#include <WindowGL.h>

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Sphere.h>
#include <Utils.h>
#include <Vertex.h>

bool WindowGL::Init()
{
    if (!glfwInit())
    {
        std::cerr << "Error initializing GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(viewportWidth_, viewportHeight_, "OpenGL - GLFW", NULL, NULL);
    if (!window_)
    {
        std::cerr << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    cameraCtrl_.Init(window_);

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE; // Needed for core profile

    GLenum err = glewInit();
    if ( err != GLEW_OK )
    {
        std::cerr << "GLEW initialization failed." << std::endl;
        glfwTerminate();
        return false;
    }

    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);

    int ver_major_min = 3;
    int ver_minor_min = 3;
    int ver_major;
    int ver_minor;
    glGetIntegerv(GL_MAJOR_VERSION, &ver_major);
    glGetIntegerv(GL_MINOR_VERSION, &ver_minor);
    if ( ver_major < ver_major_min || (ver_major >= ver_major_min && ver_minor < ver_minor_min) )
    {
        std::cerr << "Insufficient OpenGL version." << std::endl;
        glfwTerminate();
        return false;
    }

    shaderProgramId_ = InitShaders("../shaders/shader.vert",
                                   "../shaders/shader.frag",
                                   false);

    InitActors();
    SceneSetup();

    return true;
}

void WindowGL::Run()
{
    while ( glfwGetKey(window_, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window_) )
    {
        DrawScene();
        glfwPollEvents();
    }

    DeleteActors();
    glfwDestroyWindow(window_);
    glfwTerminate();
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

void WindowGL::SceneSetup()
{
    glViewport(0, 0, viewportWidth_, viewportHeight_);

    glEnable(GL_DEPTH_TEST);

    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    paramMatrixModel_ = glGetUniformLocation(shaderProgramId_, "matModel");
    paramMatrixView_  = glGetUniformLocation(shaderProgramId_, "matView");
    paramMatrixProj_  = glGetUniformLocation(shaderProgramId_, "matProj");
}

void WindowGL::DrawScene()
{
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramId_);

    cameraCtrl_.Update();
    glm::mat4 viewMatrix = cameraCtrl_.GetViewMatrix();
    glm::mat4 projMatrix = cameraCtrl_.GetProjMatrix();
    glm::mat4 modelMatrix = glm::mat4(1.0);
    glUniformMatrix4fv(paramMatrixModel_ , 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(paramMatrixView_  , 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(paramMatrixProj_  , 1, GL_FALSE, &projMatrix[0][0]);

    DrawActors();
    
    glUseProgram(0);

    glfwSwapBuffers(window_);
}

void WindowGL::InitActors()
{
    GLuint positionAttribute = glGetAttribLocation(shaderProgramId_, "position_in");
    GLuint colorAttribute = glGetAttribLocation(shaderProgramId_, "color_in");

    if ( positionAttribute == (GLuint)-1 )
    {
        positionAttribute = 0;
    }

    if ( colorAttribute == (GLuint)-1 )
    {
        colorAttribute = 3;
    }

    float r = 1.0f;
    Actor* square = new Sphere(positionAttribute, colorAttribute, r);
    actors_.push_back(square);
}

void WindowGL::DrawActors()
{
    for ( Actor* actor : actors_ )
    {
        glUniformMatrix4fv(paramMatrixModel_, 1, false, &actor->modelMatrix_[0][0]);
        actor->Draw();
    }
}

void WindowGL::DeleteActors()
{
    for ( Actor* actor : actors_ )
    {
        if ( actor )
        {
            delete actor;
            actor = nullptr;
        }
    }

    actors_.clear();
}
