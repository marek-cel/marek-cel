#ifndef DYNAMICQUADCALLBACK_H
#define DYNAMICQUADCALLBACK_H

#include <osg/Drawable>

class DynamicQuadCallback : public osg::Drawable::UpdateCallback
{
public:
    virtual void update( osg::NodeVisitor*, osg::Drawable* drawable );
};

#endif // DYNAMICQUADCALLBACK_H
