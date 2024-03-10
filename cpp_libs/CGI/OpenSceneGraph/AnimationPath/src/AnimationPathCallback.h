#ifndef ANIMATIONPATHCALLBACK_H
#define ANIMATIONPATHCALLBACK_H

#include <osg/AnimationPath>

class AnimationPathCallback : public osg::AnimationPathCallback
{
public:

    AnimationPathCallback();

    AnimationPathCallback(const AnimationPathCallback& apc,const osg::CopyOp& copyop);

    AnimationPathCallback(osg::AnimationPath* ap,double timeOffset=0.0,double timeMultiplier=1.0);

    AnimationPathCallback(const osg::Vec3d& pivot,const osg::Vec3d& axis,float angularVelocity);

    virtual double getAnimationTime() const override;

    void setValue(double value);

private:

    double value_ = 0.0;
};

#endif // ANIMATIONPATHCALLBACK_H
