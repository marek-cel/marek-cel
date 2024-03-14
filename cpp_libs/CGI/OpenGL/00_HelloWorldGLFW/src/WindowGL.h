#ifndef WINDOWGL_H_
#define WINDOWGL_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include <GLFW/glfw3.h>

class WindowGL
{
public:

    bool Init();
    void Run();

private:

    GLFWwindow* window_ = nullptr;

    int viewportWidth_ = 800;
    int viewportHeight_ = 600;

    void SceneSetup();
    void DrawScene();
};

#endif // WINDOWGL_H_