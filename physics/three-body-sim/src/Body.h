#ifndef BODY_H_
#define BODY_H_

#include <queue>

#include <osg/Group>
#include <osg/Vec3>

#include <osg/PositionAttitudeTransform>

class Body
{
public:

    static constexpr double kDT = 0.017; ///< [s]
    static constexpr double kSolarMass = 1.99e30; ///< [kg]
    static constexpr double kSolarRadius = 696000.; ///< [m]
    static constexpr double kAuToKm = 149597871;
    static constexpr double kKmToAu = 1.0 / kAuToKm;
    //static constexpr double kG = 5.93e-9;
    static constexpr double kG = 6.67e-11;

    Body(Body* bodies[], int index, int n, osg::Vec3 color,
        double mass, osg::Vec3d pos, osg::Vec3d vel);

    void update(int counter);
    void updateFine();

    inline osg::Node* getNode() { return _root.get(); }

    inline double mass() const { return _mass; }
    inline osg::Vec3d pos() const { return _pos; }

private:

    osg::ref_ptr<osg::Group> _root;
    osg::ref_ptr<osg::PositionAttitudeTransform> _pat;
    osg::ref_ptr<osg::Group> _path;

    osg::ref_ptr<osg::Vec3Array> _positions = new osg::Vec3Array();
    //osg::Vec3Array _positions;

    Body** _bodies = nullptr;

    int _index = -1;
    int _n = 0;

    osg::Vec3 _color;

    double _mass = 1.0; ///< [SM]
    double _radius = 1.0;

    osg::Vec3d _pos;    ///< [au]
    osg::Vec3d _vel;    ///< [km/s]

    osg::Vec3d _pos_prev;

    void createBody();

    void updatePath();
};

#endif // BODY_H_
