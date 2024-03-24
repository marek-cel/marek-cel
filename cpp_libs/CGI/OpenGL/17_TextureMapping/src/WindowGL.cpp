#include <WindowGL.h>

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <Box.h>
#include <Sphere.h>
#include <Square.h>

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

    std::vector<std::string> textureFiles;
    textureFiles.push_back("../../../data/land_shallow_topo_1024.jpg");
    textureFiles.push_back("../../../data/world_oceanmask_1024.jpg");
    InitTextures(textureFiles);
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
    DeleteTextures();
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

void WindowGL::InitTextures(std::vector<std::string> textureFiles)
{
    numberOfTextures_ = textureFiles.size();
    texturesIndecies_ = new GLuint [numberOfTextures_];
    glGenTextures(numberOfTextures_, texturesIndecies_);

    int width;
    int height;
    int channels;
    for ( uint16_t i = 0; i < numberOfTextures_; ++i )
    {
        if ( verbose_ )
        {
            std::cout << textureFiles[i] << std::endl;
        }

        glBindTexture(GL_TEXTURE_2D, texturesIndecies_[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        unsigned char* data = stbi_load(textureFiles[i].c_str(), &width, &height, &channels, 0);

        if ( verbose_ )
        {
            std::cout << "width: " << width << " height: " << height << " channels: " << channels << std::endl;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
}

void WindowGL::InitActors()
{
    GLuint positionAttrib = glGetAttribLocation(shaderProgramId_, "position_in");
    GLuint normalAttrib   = glGetAttribLocation(shaderProgramId_, "normal_in");
    GLuint texAttribs     = glGetAttribLocation(shaderProgramId_, "tex_in");
    GLuint colorAttrib    = glGetAttribLocation(shaderProgramId_, "color_in");

    if ( positionAttrib == (GLuint)-1 )
    {
        positionAttrib = 0;
    }

    if ( normalAttrib == (GLuint)-1 )
    {
        normalAttrib = 1;
    }

    if ( texAttribs == (GLuint)-1 )
    {
        texAttribs = 2;
    }

    if ( colorAttrib == (GLuint)-1 )
    {
        colorAttrib = 3;
    }

    float r = 1.0f;
    Actor* sphere = new Sphere(positionAttrib, normalAttrib, texAttribs, colorAttrib, r);
    sphere->ambientColor_ = glm::vec3(1,1,1);
    sphere->diffuseColor_ = glm::vec3(1,1,1);
    sphere->textureIndex_[0] = texturesIndecies_[0];
    sphere->textureIndex_[1] = texturesIndecies_[1];
    actors_.push_back(sphere);
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
    paramMatrixNorm_  = glGetUniformLocation(shaderProgramId_, "matNormal");
    paramCameraPos_   = glGetUniformLocation(shaderProgramId_, "cameraPos");

    paramAmbientColor_  = glGetUniformLocation(shaderProgramId_, "ambientColor");
    paramDiffuseColor_  = glGetUniformLocation(shaderProgramId_, "diffuseColor");
    paramSpecularColor_ = glGetUniformLocation(shaderProgramId_, "specularColor");
    paramShinessVal_    = glGetUniformLocation(shaderProgramId_, "shinessVal");
}

void WindowGL::DrawScene()
{
    //glClearColor(0.5, 0.5, 0.5, 1);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramId_);

    cameraCtrl_.Update();
    glm::mat4 viewMatrix = cameraCtrl_.GetViewMatrix();
    glm::mat4 projMatrix = cameraCtrl_.GetProjMatrix();
    glm::mat4 modelMatrix = glm::mat4(1.0);
    glm::vec3 cameraPos = cameraCtrl_.GetCameraPos();
    glUniformMatrix4fv(paramMatrixModel_ , 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(paramMatrixView_  , 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(paramMatrixProj_  , 1, GL_FALSE, &projMatrix[0][0]);
    glUniform3fv(paramCameraPos_, 1, &cameraPos[0]);

    DrawActors();
    
    glUseProgram(0);

    glfwSwapBuffers(window_);
}

void WindowGL::DrawActors()
{
    for ( Actor* actor : actors_ )
    {
        glUniformMatrix4fv(paramMatrixModel_, 1, false, &actor->modelMatrix_[0][0]);
        glm::mat3 normMatrix = glm::transpose(glm::inverse(glm::mat3(actor->modelMatrix_)));
        glUniformMatrix3fv(paramMatrixNorm_, 1, false, &normMatrix[0][0]);

        SetMaterialParams(actor->ambientColor_,
                          actor->diffuseColor_,
                          actor->specularColor_,
                          actor->shininessVal_);

        if ( actor->textureIndex_[0] != (GLuint)-1 )
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, actor->textureIndex_[0]);
            glUniform1i(glGetUniformLocation(shaderProgramId_, "texSampler0"), 0);
        }

        if ( actor->textureIndex_[1] != (GLuint)-1 )
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, actor->textureIndex_[1]);
            glUniform1i(glGetUniformLocation(shaderProgramId_, "texSampler1"), 1);
        }

        actor->Draw();
    }
}

void WindowGL::SetMaterialParams(glm::vec3 ambientColor,
                                 glm::vec3 diffuseColor,
                                 glm::vec3 specularColor,
                                 float shinessVal)
{
    glUniform3fv(paramAmbientColor_, 1, &ambientColor[0]);
    glUniform3fv(paramDiffuseColor_, 1, &diffuseColor[0]);
    glUniform3fv(paramSpecularColor_, 1, &specularColor[0]);
    glUniform1f(paramShinessVal_, shinessVal);
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

void WindowGL::DeleteTextures()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(numberOfTextures_, texturesIndecies_);
    delete [] texturesIndecies_;
    texturesIndecies_ = nullptr;
}
