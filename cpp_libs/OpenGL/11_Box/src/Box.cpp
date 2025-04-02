#include <Box.h>

Box::Box(GLuint positionAttribute, GLuint colorAttribute,
         float width, float height, float depth)
    : width_(width)
    , height_(height)
    , depth_(depth)
{
    Init(positionAttribute, colorAttribute);
}

void Box::Draw()
{
    assert(vertexCount_ > 0);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    for ( int i = 0; i < 6; ++i )
    {
        glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

unsigned int Box::CreateVertexArray(Vertex*& vertices)
{
    constexpr unsigned int vertexCount = 24;
    vertices = new Vertex [vertexCount];

    const float x0 = width_  / 2.0;
    const float y0 = height_ / 2.0;
    const float z0 = depth_  / 2.0;

    // front
    vertices[0]  = Vertex(-x0, -y0,  z0, 1, 0, 0, 1);
    vertices[1]  = Vertex( x0, -y0,  z0, 1, 0, 0, 1);
    vertices[2]  = Vertex(-x0,  y0,  z0, 1, 0, 0, 1);
    vertices[3]  = Vertex( x0,  y0,  z0, 1, 0, 0, 1);

    // back
    vertices[4]  = Vertex(-x0, -y0, -z0, 0, 1, 0, 1);
    vertices[5]  = Vertex(-x0,  y0, -z0, 0, 1, 0, 1);
    vertices[6]  = Vertex( x0, -y0, -z0, 0, 1, 0, 1);
    vertices[7]  = Vertex( x0,  y0, -z0, 0, 1, 0, 1);

    // top
    vertices[8]  = Vertex(-x0,  y0,  z0, 0, 0, 1, 1);
    vertices[9]  = Vertex( x0,  y0,  z0, 0, 0, 1, 1);
    vertices[10] = Vertex(-x0,  y0, -z0, 0, 0, 1, 1);
    vertices[11] = Vertex( x0,  y0, -z0, 0, 0, 1, 1);

    // bottom
    vertices[12] = Vertex( x0, -y0,  z0, 1, 0, 1, 1);
    vertices[13] = Vertex(-x0, -y0,  z0, 1, 0, 1, 1);
    vertices[14] = Vertex( x0, -y0, -z0, 1, 0, 1, 1);
    vertices[15] = Vertex(-x0, -y0, -z0, 1, 0, 1, 1);

    // left
    vertices[16] = Vertex(-x0, -y0, -z0, 1, 1, 0, 1);
    vertices[17] = Vertex(-x0, -y0,  z0, 1, 1, 0, 1);
    vertices[18] = Vertex(-x0,  y0, -z0, 1, 1, 0, 1);
    vertices[19] = Vertex(-x0,  y0,  z0, 1, 1, 0, 1);

    // right
    vertices[20] = Vertex( x0, -y0,  z0, 0, 1, 1, 1);
    vertices[21] = Vertex( x0, -y0, -z0, 0, 1, 1, 1);
    vertices[22] = Vertex( x0,  y0,  z0, 0, 1, 1, 1);
    vertices[23] = Vertex( x0,  y0, -z0, 0, 1, 1, 1);

    return vertexCount;
}