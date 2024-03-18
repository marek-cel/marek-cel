#ifndef CAMERACTRL_H_
#define CAMERACTRL_H_

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class CameraCtrl
{
public:

    void Init(GLFWwindow* window);

    glm::mat4 GetViewMatrix() { return viewMatrix_; }
    glm::mat4 GetProjMatrix() { return projMatrix_; }

    void Update();

private:

    GLFWwindow* window_ = nullptr;

    glm::mat4 viewMatrix_ = glm::mat4(1.0);
    glm::mat4 projMatrix_ = glm::mat4(1.0);

    float azimuth_ = 0.0f;
    float elevation_ = 0.0f;
    float distance_ = 3.0f;

    double lastTime_ = 0.0;

    //float speedDistance_ = 3.0f; // 3 units / second
    float speedDistanceFrac_ = 2.0f;
    float speedRotate_ = 0.003f;

    double xpos_prev_ = 0.0;
    double ypos_prev_ = 0.0;
};

#endif // CAMERACTRL_H_