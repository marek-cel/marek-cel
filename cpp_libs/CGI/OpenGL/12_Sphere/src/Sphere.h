#ifndef SPHERE_H_
#define SPHERE_H_

#include <vector>

#include <Actor.h>

class Sphere : public Actor 
{
public:

    Sphere(GLuint positionAttribute, GLuint colorAttribute,
           float radius, uint16_t segments = 32, uint16_t rings = 16);

protected:

    float radius_;
    uint16_t segments_;
    uint16_t rings_;

    unsigned int CreateVertexArray(Vertex*& vertices) override;

    std::vector<Vertex> CreateVertexVector();
};

#endif // SPHERE_H_