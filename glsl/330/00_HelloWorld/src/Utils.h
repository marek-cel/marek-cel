#ifndef UTILS_H_
#define UTILS_H_

#include <GL/glew.h>

#include <GL/gl.h>

float DegreesToRadians(float deg);
double DegreesToRadians(double deg);

GLuint InitShaders(const char* vertFileName, 
                   const char* fragFileName,
                   bool debug = false);

GLuint CompileShader(const char* fileName, GLenum type,
                     bool debug = false);

bool ReadFromFile(const char* fileName, GLchar* out);

#endif // UTILS_H_