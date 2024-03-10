#ifndef TRANSPARENCYTECHNIQUE_H
#define TRANSPARENCYTECHNIQUE_H

#include <osg/ColorMask>
#include <osg/Depth>

#include <osgFX/Technique>

class TransparencyTechnique : public osgFX::Technique
{
public:

    TransparencyTechnique() : osgFX::Technique() {}

    virtual bool validate( osg::State& ss ) const { return true; }

protected:

    virtual void define_passes()
    {
        osg::ref_ptr<osg::StateSet> ss = new osg::StateSet;
        ss->setAttributeAndModes( new osg::ColorMask(false, false, false, false) );
        ss->setAttributeAndModes( new osg::Depth(osg::Depth::LESS) );
        addPass( ss.get() );

        ss = new osg::StateSet;
        ss->setAttributeAndModes( new osg::ColorMask(true, true, true, true) );
        ss->setAttributeAndModes( new osg::Depth(osg::Depth::EQUAL) );
        addPass( ss.get() );
    }
};

#endif // TRANSPARENCYTECHNIQUE_H