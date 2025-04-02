#ifndef ACTOR_H_
#define ACTOR_H_

#include <GL/glew.h>

#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Vertex.h>

class Actor 
{
public:

    glm::mat4 modelMatrix_ = glm::mat4(1.0);

    glm::vec3 ambientColor_  = glm::vec3(1,0,0);
    glm::vec3 diffuseColor_  = glm::vec3(1,0,0);
    glm::vec3 specularColor_ = glm::vec3(1,1,1);
    float shininessVal_ = 32.0;

    GLuint textureIndex_ = (GLuint)-1;
    
    Actor() = default;
    virtual ~Actor();

    virtual void Init(GLuint positionAttrib,
                      GLuint normalAttrib,
                      GLuint texAttribs,
                      GLuint colorAttrib);
    virtual void Draw();

    void SetPosition(const glm::vec3& vec);
    void SetPosition(double x, double y, double z);

protected:

    GLuint vao_ = GLuint(-1);
    GLuint vbo_ = GLuint(-1);

    unsigned int vertexCount_ = -1;

    virtual unsigned int CreateVertexArray(Vertex*& vertices) = 0;

private:

    void InitVertexBuffer();
    void DeleteVertexBuffer();

};

#endif // ACTOR_H_