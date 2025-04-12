#include <iostream>
#include <cmath>
#include <array>

const double dt = 0.01; // timestep
const int steps = 1000;
const double pi = 3.141592653589793;

struct Vec3
{
    double x, y, z;

    Vec3 operator+(const Vec3& rhs) const
    {
        return {x + rhs.x, y + rhs.y, z + rhs.z};
    }

    Vec3 operator-(const Vec3& rhs) const
    {
        return {x - rhs.x, y - rhs.y, z - rhs.z};
    }

    Vec3 operator*(double s) const
    {
        return {x * s, y * s, z * s};
    }

    Vec3& operator+=(const Vec3& rhs)
    {
        x += rhs.x; y += rhs.y; z += rhs.z;
        return *this;
    }
};

Vec3 cross(const Vec3& a, const Vec3& b)
{
    return
    {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

struct Quaternion
{
    double w, x, y, z;

    static Quaternion identity()
    {
        return {1, 0, 0, 0};
    }

    Quaternion operator*(const Quaternion& q) const
    {
        return
        {
            w*q.w - x*q.x - y*q.y - z*q.z,
            w*q.x + x*q.w + y*q.z - z*q.y,
            w*q.y - x*q.z + y*q.w + z*q.x,
            w*q.z + x*q.y - y*q.x + z*q.w
        };
    }

    Quaternion normalize() const
    {
        double norm = std::sqrt(w*w + x*x + y*y + z*z);
        return {w/norm, x/norm, y/norm, z/norm};
    }

    void integrateAngularVelocity(const Vec3& omega, double dt)
    {
        Quaternion dq = {0, omega.x, omega.y, omega.z};
        Quaternion result = *this * dq;
        w += 0.5 * result.w * dt;
        x += 0.5 * result.x * dt;
        y += 0.5 * result.y * dt;
        z += 0.5 * result.z * dt;
        *this = normalize();
    }
};

struct RigidBody
{
    Vec3 position;
    Quaternion orientation;
    Vec3 velocity;
    Vec3 angularVelocity;

    void integrate(double dt)
    {
        position += velocity * dt;
        orientation.integrateAngularVelocity(angularVelocity, dt);
    }
};

void applyHingeConstraint(RigidBody& trailer, const RigidBody& tractor)
{
    // Hinge around Y axis of the tractor
    trailer.position = tractor.position - Vec3{2.0, 0, 0}; // fixed offset
    trailer.velocity = tractor.velocity;

    // Allow only Y-axis rotation
    trailer.angularVelocity = {0.0, trailer.angularVelocity.y, 0.0};
}

int main()
{
    RigidBody tractor =
    {
        {0, 0, 0}, Quaternion::identity(), {1, 0, 0}, {0, 0.1, 0}
    };

    RigidBody trailer =
    {
        {-2, 0, 0}, Quaternion::identity(), {1, 0, 0}, {0, 0, 0}
    };

    for (int i = 0; i < steps; ++i)
    {
        applyHingeConstraint(trailer, tractor);

        tractor.integrate(dt);
        trailer.integrate(dt);

        std::cout << "Step " << i << ":\n";
        std::cout << "  Tractor Position: (" << tractor.position.x << ", " << tractor.position.y << ", " << tractor.position.z << ")\n";
        std::cout << "  Trailer Position: (" << trailer.position.x << ", " << trailer.position.y << ", " << trailer.position.z << ")\n";
    }

    return 0;
}