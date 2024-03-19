#ifndef SPHERE_H_
#define SPHERE_H_

#include <vector>

#include <Actor.h>

class Sphere : public Actor 
{
public:

    enum class Projection
    {
        Azimuthal,
        Cylindrical
    };

    Sphere(GLuint positionAttrib,
           GLuint normalAttrib,
           GLuint texAttribs,
           GLuint colorAttrib,
           float radius,
           uint16_t segments = 32,
           uint16_t rings = 16,
           Projection proj = Projection::Cylindrical);

protected:

    float radius_;
    uint16_t segments_;
    uint16_t rings_;

    Projection proj_ = Projection::Cylindrical;

    unsigned int CreateVertexArray(Vertex*& vertices) override;

    std::vector<Vertex> CreateVertexVector();
};

#endif // SPHERE_H_