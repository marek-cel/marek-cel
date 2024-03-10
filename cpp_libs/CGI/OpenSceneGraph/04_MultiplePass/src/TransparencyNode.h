#ifndef TRANSPARENCYNODE_H
#define TRANSPARENCYNODE_H

#include <osgFX/Effect>

#include <TransparencyTechnique.h>

class TransparencyNode : public osgFX::Effect
{
public:

    TransparencyNode() : osgFX::Effect() {}

    TransparencyNode( const TransparencyNode& copy,
                      const osg::CopyOp op=osg::CopyOp::SHALLOW_COPY ) :
        osgFX::Effect(copy, op)
    {}

    META_Effect( osgFX, TransparencyNode, "TransparencyNode", "", "" )

protected:

    virtual bool define_techniques()
    {
        addTechnique(new TransparencyTechnique);
        return true;
    }
};

#endif // TRANSPARENCYNODE_H