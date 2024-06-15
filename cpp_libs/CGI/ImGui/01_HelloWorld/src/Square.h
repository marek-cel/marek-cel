#ifndef SQUARE_H_
#define SQUARE_H_

#include <Actor.h>

class Square : public Actor 
{
public:

    Square(GLuint positionAttrib,
           GLuint normalAttrib,
           GLuint texAttribs,
           GLuint colorAttrib,
           float sideLength);

protected:

    float sideLength_;

    unsigned int CreateVertexArray(Vertex*& vertices) override;
};

#endif // SQUARE_H_