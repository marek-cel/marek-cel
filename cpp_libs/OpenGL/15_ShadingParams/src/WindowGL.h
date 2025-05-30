#ifndef WINDOWGL_H_
#define WINDOWGL_H_

#include <vector>

#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <GLFW/glfw3.h>

#include <Actor.h>
#include <CameraCtrl.h>

class WindowGL
{
public:

    using Actors = std::vector<Actor*>;

    bool Init();
    void Run();

private:

    GLFWwindow* window_ = nullptr;

    Actors actors_;
    CameraCtrl cameraCtrl_;

    int viewportWidth_ = 800;
    int viewportHeight_ = 600;

    unsigned int shaderProgramId_;

    GLint paramMatrixView_  = (GLuint)-1;
    GLint paramMatrixProj_  = (GLuint)-1;
    GLint paramMatrixModel_ = (GLuint)-1;
    GLint paramMatrixNorm_  = (GLuint)-1;
    GLint paramCameraPos_   = (GLuint)-1;

    GLint paramAmbientColor_  = (GLuint)-1;
    GLint paramDiffuseColor_  = (GLuint)-1;
    GLint paramSpecularColor_ = (GLuint)-1;
    GLint paramShinessVal_    = (GLuint)-1;

    void PrintInfo();
    void SceneSetup();
    void DrawScene();

    void SetMaterialParams(glm::vec3 ambientColor,
                           glm::vec3 diffuseColor,
                           glm::vec3 specularColor,
                           float shinessVal);

    void InitActors();
    void DrawActors();
    void DeleteActors();
};

#endif // WINDOWGL_H_