#include <Utils.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>


GLuint InitShaders(const char* vertFileName, 
                   const char* fragFileName,
                   bool debug)
{
    GLuint vertShaderId = CompileShader(vertFileName, GL_VERTEX_SHADER   , debug);
    GLuint fragShaderId = CompileShader(fragFileName, GL_FRAGMENT_SHADER , debug);

    if ( vertShaderId == 0 )
    {
        std::cerr << "Error compiling vertex shader." << std::endl;
        return 0;
    }

    if ( fragShaderId == 0 )
    {
        std::cerr << "Error compiling fragment shader." << std::endl;
        return 0;
    }

    GLuint programId = glCreateProgram();

    glAttachShader(programId, vertShaderId);
    glAttachShader(programId, fragShaderId);

    glLinkProgram(programId);

    GLint result;
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    if ( !result )
    {
        GLchar infoLog[2048];
        glGetProgramInfoLog(programId, 2048, 0, infoLog);
        std::cerr << "Program linking failed." << std::endl;
        std::cerr << infoLog << std::endl;
        return 0;
    }
    else
    {
        if ( debug )
        {
            std::cout << "Program linking successfull." << std::endl;
        }
    }

    glGetProgramiv(programId, GL_VALIDATE_STATUS, &result);
    if ( !result )
    {
        GLchar infoLog[2048];
        glGetProgramInfoLog(programId, 2048, 0, infoLog);
        std::cerr << "Program validation failed." << std::endl;
        std::cerr << infoLog << std::endl;
        return 0;
    }
    else
    {
        if ( debug )
        {
            std::cout << "Program validation successfull." << std::endl;
        }
    }

    glUseProgram(programId);

    glDeleteShader(vertShaderId);
    glDeleteShader(fragShaderId);

    return programId;
}

GLuint CompileShader(const char* fileName, GLenum type,
                     bool debug)
{
    GLchar code[65535];
    ReadFromFile(fileName, code);
    if ( debug )
    {
        std::cout << code;
    }

    GLuint shaderId = glCreateShader(type);
    if ( shaderId == 0 )
    {
        return 0;
    }

    GLchar* buff[1];
    buff[0] = code;
    glShaderSource(shaderId, 1, buff, 0);

    glCompileShader(shaderId);

    GLint result;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    if ( !result )
    {
        GLchar infoLog[2048];
        glGetShaderInfoLog(shaderId, 2048, 0, infoLog);
        std::cerr << "Shader compilation failed." << std::endl;
        std::cerr << infoLog << std::endl;
        return 0;
    }
    else
    {
        if ( debug )
        {
            std::cout << "Shader compilation successfull." << std::endl;
        }
    }

    return shaderId;
}

bool ReadFromFile(const char* fileName, GLchar* out)
{
    std::ifstream ifs(fileName, std::ifstream::in);
    if ( ifs.is_open() )
    {
        std::string code;
        std::string line;
        while ( getline(ifs, line) )
        {
            code += line + "\n";
        }
        ifs.close();
        strcpy(out, code.c_str());
    }
    else
    {
        std::cerr << "Cannot open file: " << fileName << std::endl;
        return false;
    }

    return true;
}