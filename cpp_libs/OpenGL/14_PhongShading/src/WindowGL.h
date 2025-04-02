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

    GLint paramMatrixView_;
    GLint paramMatrixProj_;
    GLint paramMatrixModel_;
    GLint paramMatrixNorm_;
    GLint paramCameraPos_;

    void PrintInfo();
    void SceneSetup();
    void DrawScene();

    void InitActors();
    void DrawActors();
    void DeleteActors();
};

#endif // WINDOWGL_H_