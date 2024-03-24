#include <ComputeTangentVisitor.h>

#include <iostream>

#include <osg/Geode>

#include <osgUtil/TangentSpaceGenerator>

void ComputeTangentVisitor::apply(osg::Geode& node)
{
        for ( unsigned int i = 0; i < node.getNumDrawables(); ++i )
        {
            osg::Geometry* geom = dynamic_cast<osg::Geometry*>(node.getDrawable(i));
            if ( geom ) generateTangentArray(geom);
        }

        traverse(node);
}

void ComputeTangentVisitor::generateTangentArray(osg::Geometry* geom)
{
    osg::ref_ptr<osgUtil::TangentSpaceGenerator> tsg = new osgUtil::TangentSpaceGenerator();
    
    tsg->generate(geom);
    
    geom->setVertexAttribArray(6, tsg->getTangentArray());
    geom->setVertexAttribBinding(6, osg::Geometry::BIND_PER_VERTEX);
    geom->setVertexAttribArray(7, tsg->getBinormalArray());
    geom->setVertexAttribBinding(7, osg::Geometry::BIND_PER_VERTEX);

    // for ( int i = 0; i < tsg->getTangentArray()->size(); ++i )
    // {
    //     osg::Vec4 v = (*tsg->getTangentArray())[i];
    //     std::cout << v.x() << " " << v.y() << " " << v.z() << std::endl;
    // }
}