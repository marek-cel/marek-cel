#ifndef UTILS_H_
#define UTILS_H_

#include <osg/Texture2D>

float deg2rad(float deg);
std::string readShaderFromFile(const char* path);
osg::Texture2D* readTextureFromFile(const char* path);

#endif // UTILS_H_
