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
    
    Actor() = default;
    virtual ~Actor();

    virtual void Init(GLuint positionAttribute, GLuint colorAttribute);
    virtual void Draw();

protected:

    //glm::mat4 modelMatrix_ = glm::mat4(1.0);

    GLuint vao_ = GLuint(-1);
    GLuint vbo_ = GLuint(-1);

    unsigned int vertexCount_ = -1;

    virtual unsigned int CreateVertexArray(Vertex*& vertices) = 0;

private:

    void InitVertexBuffer();
    void DeleteVertexBuffer();

};

#endif // ACTOR_H_