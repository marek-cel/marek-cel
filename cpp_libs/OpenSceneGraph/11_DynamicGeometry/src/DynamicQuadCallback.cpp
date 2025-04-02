#include <DynamicQuadCallback.h>

#include <osg/Geometry>

void DynamicQuadCallback::update(osg::NodeVisitor*, osg::Drawable* drawable)
{
    osg::Geometry* quad = static_cast<osg::Geometry*>( drawable );
    if ( !quad ) return;
    osg::Vec3Array* vertices = static_cast<osg::Vec3Array*>( quad->getVertexArray() );
    if ( !vertices ) return;
    osg::Quat quat(osg::PI*0.01, osg::X_AXIS);
    vertices->back() = quat * vertices->back();
    //quad->dirtyDisplayList();
    vertices->dirty();
    quad->dirtyBound();
}
