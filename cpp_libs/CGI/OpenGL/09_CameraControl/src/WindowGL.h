#ifndef WINDOWGL_H_
#define WINDOWGL_H_

#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <GLFW/glfw3.h>

#include <CameraCtrl.h>

class WindowGL
{
public:

    bool Init();
    void Run();

private:

    GLFWwindow* window_ = nullptr;

    CameraCtrl cameraCtrl_;

    int viewportWidth_ = 800;
    int viewportHeight_ = 600;

    unsigned int vao_;
    unsigned int vbo_[3];

    unsigned int shaderProgramId_;

    GLint paramMatrixView_;
    GLint paramMatrixProj_;
    GLint paramMatrixModel_;

    void PrintInfo();
    void SceneSetup();
    void InitVertexBuffer();
    void DrawScene();
    void DeleteVertexBuffer();
};

#endif // WINDOWGL_H_