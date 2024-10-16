#ifndef BOX_H_
#define BOX_H_

#include <Actor.h>

class Box : public Actor 
{
public:

    Box(GLuint positionAttribute, GLuint colorAttribute,
        float width, float height, float depth);
    
    void Draw() override;

protected:

    float width_;
    float height_;
    float depth_;

    unsigned int CreateVertexArray(Vertex*& vertices) override;
};

#endif // BOX_H_