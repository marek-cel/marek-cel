#include <WindowGL.h>

#include <iostream>
#include <string>

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

    window_ = glfwCreateWindow(viewportWidth_, viewportHeight_, "OpenGL - GLFW", nullptr, nullptr);
    if (!window_)
    {
        std::cerr << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window_);

    glewExperimental = GL_TRUE;

    GLenum err = glewInit();
    if ( err != GLEW_OK )
    {
        std::cerr << "GLEW initialization failed." << std::endl;
        glfwTerminate();
        return false;
    }

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
                                   true);

    InitVertexBuffer();
    SceneSetup();

    return true;
}

void WindowGL::Run()
{
    while (!glfwWindowShouldClose(window_))
    {
        DrawScene();
        glfwPollEvents();
    }

    DeleteVertexBuffer();
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
    glEnable(GL_DEPTH_TEST);

    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    GLint paramUseVertexColor = glGetUniformLocation(shaderProgramId_, "UseVertexColor");
    glUniform1i(paramUseVertexColor, false);

    GLint paramColor = glGetUniformLocation(shaderProgramId_, "Color");
    float color[4] = { 1.0, 0.0, 1.0, 1.0 };
    glUniform4fv(paramColor, 1, color);

    GLint paramWave = glGetUniformLocation(shaderProgramId_, "Wave");
    glUniform1i(paramWave, true);

    GLint paramWaveColor = glGetUniformLocation(shaderProgramId_, "WaveColor");
    float waveColor[4] = { 1.0, 1.0, 0.0, 1.0 };
    glUniform4fv(paramWaveColor, 1, waveColor);
}

void WindowGL::InitVertexBuffer()
{
    float size = 0.5;
    float z = -1.0;
    const Vertex vertices[] = 
    {
        Vertex(-size, -size, z, 1, 0, 0, 1),
        Vertex( size, -size, z, 0, 1, 0, 1),
        Vertex(-size,  size, z, 1, 1, 0, 1),
        Vertex( size,  size, z, 1, 0, 1, 1)
    };

    GLuint positionAttribute = glGetAttribLocation(shaderProgramId_, "position_in");
    GLuint colorsAttribute = glGetAttribLocation(shaderProgramId_, "color_in");

    if ( positionAttribute == (GLuint)-1 )
    {
        positionAttribute = 0;
    }

    if ( colorsAttribute == (GLuint)-1 )
    {
        colorsAttribute = 3;
    }

    // Generate and bind Vertex Array Object (VAO)
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // Vertex Buffer Object (VBO)
    glGenBuffers(3, &vbo_[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(positionAttribute, Vertex::positionCoordinatesCount, 
        GL_FLOAT, GL_FALSE, Vertex::vertexVectorSize, 0);
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(colorsAttribute, Vertex::colorElementsCount, 
        GL_FLOAT, GL_FALSE, Vertex::vertexVectorSize, (const GLvoid*)Vertex::positionVectorSize);
    glEnableVertexAttribArray(colorsAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind VAO
    glBindVertexArray(0); 
}

void WindowGL::DrawScene()
{
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramId_);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(window_);
}

void WindowGL::DeleteVertexBuffer()
{
    glDeleteBuffers(3, vbo_);
    glDeleteVertexArrays(1, &vao_);
}