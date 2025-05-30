#include <Sphere.h>

#include <Utils.h>

Sphere::Sphere(GLuint positionAttrib,
               GLuint normalAttrib,
               GLuint texAttribs,
               GLuint colorAttrib,
               float radius,
               uint16_t segments,
               uint16_t rings,
               Projection proj)
    : radius_(radius)
    , segments_(segments)
    , rings_(rings)
    , proj_(proj)
{
    Init(positionAttrib, normalAttrib, texAttribs, colorAttrib);
}

unsigned int Sphere::CreateVertexArray(Vertex*& vertices)
{
    std::vector<Vertex> v_temp = CreateVertexVector();

    const uint16_t vertexCount = v_temp.size();
    vertices = new Vertex [vertexCount];

    for ( uint16_t i = 0; i < vertexCount; ++i )
    {
        vertices[i] = v_temp[i];
    }

    return vertexCount;
}

std::vector<Vertex> Sphere::CreateVertexVector()
{
    std::vector<Vertex> v;

    const float cr = 1.0;
    const float cg = 0.0;
    const float cb = 0.0;

    float lat_step = DegreesToRadians(180.0f) / (double)rings_;
    float lon_step = DegreesToRadians(360.0f) / (double)segments_;

    float lat_prev = DegreesToRadians(90.0f);
    float lat_next = DegreesToRadians(90.0f) - lat_step;
    float lon_prev = 0.0f;

    float x_prev = 0.0f;
    float y_prev = 0.0f;
    float z_prev = radius_;

    double x_next = 0.0;
    double y_next = 0.0;
    double z_next = radius_;

    double r_prev = 0.0;
    double r_next = 0.0;

    for ( int i_lat = 0; i_lat < rings_; i_lat++ )
    {
        if ( lat_next < DegreesToRadians(-90.0f) )
        {
            lat_next = DegreesToRadians(-90.0f);
        }

        z_prev = radius_ * sin(lat_prev);
        r_prev = radius_ * cos(lat_prev);

        for ( int i_lon = 0; i_lon < segments_ + 1; i_lon++ )
        {
            lon_prev = i_lon * lon_step;

            x_prev = r_prev * cos(lon_prev - M_PI);
            y_prev = r_prev * sin(lon_prev - M_PI);

            z_next = radius_ * sin(lat_next);
            r_next = radius_ * cos(lat_next);

            x_next = r_next * cos(lon_prev - M_PI);
            y_next = r_next * sin(lon_prev - M_PI);

            glm::vec3 p_prev(x_prev, y_prev, z_prev);
            glm::vec3 p_next(x_next, y_next, z_next);

            glm::vec3 n_prev = glm::normalize(p_prev);
            glm::vec3 n_next = glm::normalize(p_next);

            float s_prev = 0.0f;
            float t_prev = 0.0f;
            float s_next = 0.0f;
            float t_next = 0.0f;

            if ( proj_ == Projection::Azimuthal )
            {
                float n_arc_prev = (M_PI_2 - fabs(lat_prev)) / M_PI_2;
                float n_arc_next = (M_PI_2 - fabs(lat_next)) / M_PI_2;

                s_prev = 0.5 + 0.5 * n_arc_prev * sin(lon_prev);
                t_prev = 0.5 + 0.5 * n_arc_prev * cos(lon_prev);
                s_next = 0.5 + 0.5 * n_arc_next * sin(lon_prev);
                t_next = 0.5 + 0.5 * n_arc_next * cos(lon_prev);
            }
            else if ( proj_ == Projection::Cylindrical )
            {
                s_prev = static_cast<double>(i_lon)/segments_;
                t_prev = static_cast<double>(i_lat)/rings_;
                s_next = static_cast<double>(i_lon)/segments_;
                t_next = static_cast<double>(i_lat+1)/rings_;
            }

            v.push_back(Vertex(x_prev, y_prev, z_prev, n_prev.x, n_prev.y, n_prev.z, s_prev, t_prev, cr, cg, cb, 1.0));
            v.push_back(Vertex(x_next, y_next, z_next, n_next.x, n_next.y, n_next.z, s_next, t_next, cr, cg, cb, 1.0));
        }

        lat_prev -= lat_step;
        lat_next -= lat_step;
    }

    return v;
}