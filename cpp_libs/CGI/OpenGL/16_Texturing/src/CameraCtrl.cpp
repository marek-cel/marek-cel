#include <CameraCtrl.h>

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

double g_xoffset = 0.0;
double g_yoffset = 0.0;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    g_xoffset = xoffset;
    g_yoffset = yoffset;
}

void CameraCtrl::Init(GLFWwindow* window)
{ 
    lastTime_ = glfwGetTime();
    window_ = window; 
    glfwSetScrollCallback(window_, scroll_callback);
}

void CameraCtrl::Update()
{
    double currentTime = glfwGetTime();
	float deltaTime = static_cast<float>(currentTime - lastTime_);

    int width, height;
    glfwGetWindowSize(window_, &width, &height);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window_, &xpos, &ypos);

    if ( glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS )
    {
        float delta_x = xpos - xpos_prev_;
        float delta_y = ypos - ypos_prev_;
        azimuth_   -= speedRotate_ * delta_x;
	    elevation_ += speedRotate_ * delta_y;
    }

    glm::vec3 direction(
		cos(elevation_) * sin(azimuth_), 
		sin(elevation_),
		cos(elevation_) * cos(azimuth_)
	);

	glm::vec3 right = glm::vec3(
		sin(azimuth_ - M_PI_2), 
		0,
		cos(azimuth_ - M_PI_2)
	);

    glm::vec3 up = glm::cross(right, direction);

    cameraPos_ = direction * distance_;
    glm::vec3 center;

	// Move forward
	// if (glfwGetKey( window_, GLFW_KEY_W ) == GLFW_PRESS)
    // {
	// 	distance_ -= deltaTime * speedDistance_;
	// }
	// // Move backward
	// if (glfwGetKey( window_, GLFW_KEY_S ) == GLFW_PRESS)
    // {
	// 	distance_ += deltaTime * speedDistance_;
	// }
    distance_ += deltaTime * speedDistanceFrac_ * fabs(distance_) * g_yoffset;
    g_yoffset = 0.0;

    if ( distance_ < 0.0f ) distance_ = 0.0f;

    viewMatrix_ = glm::lookAt(cameraPos_, center, up);

    double h2w = static_cast<double>(height) / static_cast<double>(width);
    projMatrix_ = glm::frustum(-1.0, 1.0, -1.0*h2w, 1.0*h2w, 1.0, 10.0);

    lastTime_ = currentTime;

    xpos_prev_ = xpos;
    ypos_prev_ = ypos;
}