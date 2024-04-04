#include <Body.h>

#include <cmath>
#include <iostream>

#include <osg/Geode>
#include <osg/LineWidth>
#include <osg/Point>
#include <osg/ShapeDrawable>

#define CGI_SKYDOME_DIAMETER_SUN 0.54

Body::Body(Body* bodies[], int index, int n, osg::Vec3 color,
        double mass, osg::Vec3d pos, osg::Vec3d vel)
    : _bodies(bodies)
    , _index(index)
    , _n(n)
    , _color(color)
    , _mass(mass)
    , _radius(pow(_mass, 1.0/3.0))
    , _pos(pos)
    , _vel(vel)
{
    _pos_prev = _pos;

    _root = new osg::Group();
    createBody();

    _path = new osg::Group();
    _root->addChild(_path.get());

    _path->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
}

void Body::update(int counter)
{
    //std::cout << std::endl;

    double m1 = _mass * kSolarMass;

    osg::Vec3d force;
    for ( int i = 0; i < _n; ++i )
    {
        if ( i != _index )
        {
            double m2 = _bodies[i]->mass() * kSolarMass;
            osg::Vec3d v_dist = _bodies[i]->_pos_prev - _pos;
            double dist = v_dist.length() * kAuToKm * 1000.0;
            double r_t = (_radius + _bodies[i]->_radius) * kSolarRadius;
            double r_m = std::max(dist, 100.0*r_t);
            //std::cout << r_m << std::endl;
            v_dist.normalize();
            double f = kG * (((m1 / r_m) / kSolarMass) * ((m2 / r_m) / 1000.0));
            // if ( dist < r_t )
            // {
            //     f = f - 1.0e9 * pow(r_t - dist, 2.0);
            // }

            force = force + (v_dist * f);
            //std::cout << f << std::endl;
        }
    }

    //std::cout << force.x() << " " << force.y() << " " << force.z() << std::endl;

    osg::Vec3d acc = force / _mass;
    //std::cout << acc.x() << " " << acc.y() << " " << acc.z() << std::endl;
    double coef = kDT * 3600.0 * 24.0;
    _vel = _vel + acc * coef;
    osg::Vec3d vel = _vel * kKmToAu;
    _pos = _pos + vel * coef;

    //std::cout << _pos.x() << " " << _pos.y() << " " << _pos.z() << std::endl;

    _pat->setPosition(_pos);

    if ( counter == 0 )
    {
        updatePath();
    }
}

void Body::updateFine()
{
    _pos_prev = _pos;
}

void Body::createBody()
{
    _pat = new osg::PositionAttitudeTransform();
    _root->addChild(_pat.get());

    _pat->setPosition(_pos);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _pat->addChild(geode.get());

    osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(osg::Vec3f(), _radius * 0.5);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(sphere.get());
    shape->setColor(osg::Vec4(_color, 1.0));
    geode->addDrawable(shape.get());
}

void Body::updatePath()
{
    if ( _path->getNumChildren() > 0 )
    {
        _path->removeChildren(0, _path->getNumChildren());
    }

    _positions->push_back(_pos);

    if ( _positions->size() > 5000 )
    {
        _positions->erase(_positions->begin(), _positions->begin() + 1);
    }

    // std::cout << std::endl;
    // for ( int i = 0; i < _positions->size(); i++ )
    // {
    //     std::cout << _positions->at(i).x() << " " << _positions->at(i).y() << " " <<_positions->at(i).z() << std::endl;
    // }

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    _path->addChild( geode.get() );

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();  // normals
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();  // normals
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();  // colors

    v->push_back( _pos );
    v->push_back( _pos_prev );
    n->push_back( osg::Vec3( 0.0f, 0.0f, 1.0f ) );
    c->push_back(osg::Vec4(_color, 1.0));

    // geometry->setVertexArray( v.get() );
    // geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINES, 0, v->size() ) );
    geometry->setVertexArray( _positions.get() );
    geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINE_STRIP, 0, _positions->size() ) );

    geometry->setNormalArray( n.get() );
    geometry->setNormalBinding( osg::Geometry::BIND_OVERALL );
    geometry->setColorArray( c.get() );
    geometry->setColorBinding( osg::Geometry::BIND_OVERALL );

    geode->addDrawable( geometry.get() );

    osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth();
    lineWidth->setWidth( 2.0f );

    geode->getOrCreateStateSet()->setAttributeAndModes( lineWidth, osg::StateAttribute::ON );

    //geode->getOrCreateStateSet()->setAttribute( new osg::Point( 3.0f ), osg::StateAttribute::ON );
}
