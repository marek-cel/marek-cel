#include <Actor.h>

#include <cassert>

Actor::~Actor()
{
    DeleteVertexBuffer();
}

void Actor::Init(GLuint positionAttrib, GLuint normalAttrib, GLuint colorAttrib)
{
    InitVertexBuffer();

    glVertexAttribPointer(positionAttrib, Vertex::positionCoordinatesCount, 
        GL_FLOAT, GL_FALSE, Vertex::vertexVectorSize, 0);
    glEnableVertexAttribArray(positionAttrib);

    glVertexAttribPointer(normalAttrib, Vertex::normalElementsCount, 
        GL_FLOAT, GL_FALSE, Vertex::vertexVectorSize, (const GLvoid*)Vertex::positionVectorSize);
    glEnableVertexAttribArray(normalAttrib);

    glVertexAttribPointer(colorAttrib, Vertex::colorElementsCount, 
        GL_FLOAT, GL_FALSE, Vertex::vertexVectorSize, (const GLvoid*)(Vertex::positionVectorSize + Vertex::normalVectorSize));
    glEnableVertexAttribArray(colorAttrib);
}

void Actor::Draw()
{
    assert(vertexCount_ > 0);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount_);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Actor::SetPosition(const glm::vec3& vec)
{
    modelMatrix_ = glm::translate(glm::mat4(1.0), vec);
}

void Actor::SetPosition(double x, double y, double z)
{
    SetPosition(glm::vec3(x, y, z));
}

void Actor::InitVertexBuffer()
{
    // Generate and bind Vertex Array Object (VAO)
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // Vertex Buffer Object (VBO)
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    Vertex* vertices = nullptr;
    vertexCount_ = CreateVertexArray(vertices);
    glBufferData(GL_ARRAY_BUFFER, vertexCount_*sizeof(Vertex), vertices, GL_STATIC_DRAW);
    delete [] vertices;
}

void Actor::DeleteVertexBuffer()
{
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
}