#include <Square.h>

Square::Square(GLuint positionAttrib, 
               GLuint normalAttrib, 
               GLuint colorAttrib,
               float sideLength)
    : sideLength_(sideLength)
{
    Init(positionAttrib, normalAttrib, colorAttrib);
}

unsigned int Square::CreateVertexArray(Vertex*& vertices)
{
    constexpr unsigned int vertexCount = 4;
    vertices = new Vertex [vertexCount];

    const float x0 = sideLength_ / 2.0;
    const float y0 = sideLength_ / 2.0;

    vertices[0] = Vertex(-x0, -y0, 0.0, 0, 0, 1, 1, 0, 0, 1);
    vertices[1] = Vertex( x0, -y0, 0.0, 0, 0, 1, 0, 1, 0, 1);
    vertices[2] = Vertex(-x0,  y0, 0.0, 0, 0, 1, 1, 1, 0, 1);
    vertices[3] = Vertex( x0,  y0, 0.0, 0, 0, 1, 1, 0, 1, 1);

    return vertexCount;
}