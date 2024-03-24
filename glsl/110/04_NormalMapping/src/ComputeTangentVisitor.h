#ifndef COMPUTETANGENTVISITOR_H_
#define COMPUTETANGENTVISITOR_H_

#include <osg/NodeVisitor>


class ComputeTangentVisitor : public osg::NodeVisitor
{
public:

    void apply(osg::Node& node) { traverse(node); }

    void apply(osg::Geode& node);

    void generateTangentArray(osg::Geometry* geom);
};

#endif // COMPUTETANGENTVISITOR_H_
