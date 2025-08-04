#pragma once

#include <osgGA/GUIEventAdapter>
#include <GLFW/glfw3.h>

osgGA::GUIEventAdapter::KeySymbol convertKeyFromGlfwToOsg(const int& key);