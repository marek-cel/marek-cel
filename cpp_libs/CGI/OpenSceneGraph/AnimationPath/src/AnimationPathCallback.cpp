#include "AnimationPathCallback.h"

AnimationPathCallback::AnimationPathCallback()
    : osg::AnimationPathCallback()
{}

AnimationPathCallback::AnimationPathCallback(const AnimationPathCallback& apc, const osg::CopyOp& copyop)
    : osg::AnimationPathCallback(apc, copyop)
{}

AnimationPathCallback::AnimationPathCallback(osg::AnimationPath* ap, double timeOffset, double timeMultiplier)
    : osg::AnimationPathCallback(ap, timeOffset, timeMultiplier)
{}

AnimationPathCallback::AnimationPathCallback(const osg::Vec3d& pivot, const osg::Vec3d& axis, float angularVelocity)
    : osg::AnimationPathCallback(pivot, axis, angularVelocity)
{}

double AnimationPathCallback::getAnimationTime() const
{
    return value_;
}

void AnimationPathCallback::setValue(double value)
{
    value_ = value;
}
