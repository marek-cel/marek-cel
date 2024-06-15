#ifndef WINDOWGL_H_
#define WINDOWGL_H_

#include <string>
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

    GLuint numberOfTextures_ = 0;
    GLuint* texturesIndecies_ = nullptr;

    bool verbose_ = true;

    void PrintInfo();

    void InitImGui();

    void InitTextures(std::vector<std::string> textureFiles);
    void InitActors();
    void SceneSetup();

    void DrawImGui();
    void DrawScene();
    void DrawActors();

    void SetMaterialParams(glm::vec3 ambientColor,
                           glm::vec3 diffuseColor,
                           glm::vec3 specularColor,
                           float shinessVal);

    void DeleteActors();
    void DeleteTextures();
};

#endif // WINDOWGL_H_