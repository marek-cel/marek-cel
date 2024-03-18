#ifndef VERTEX_H_
#define VERTEX_H_

struct Vertex
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float a = 0.0f;

    static const int positionCoordinatesCount = 3;
    static const int positionVectorSize = positionCoordinatesCount * sizeof(float);

    static const int colorElementsCount = 4;
    static const int colorVectorSize = colorElementsCount * sizeof(float);

    static const int vertexVectorSize = positionVectorSize + colorVectorSize;

    Vertex() = default;
    Vertex(float x, float y, float z, float r, float g, float b, float a)
        : x(x), y(y), z(z), r(r), g(g), b(b), a(a)
    {}
};

#endif // VERTEX_H_