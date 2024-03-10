#include <SwitchingCallback.h>

#include <osg/Switch>

void SwitchingCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
    osg::Switch* switchNode = static_cast<osg::Switch*>( node );
    if ( !((++_count)%60) && switchNode )
    {
    switchNode->setValue( 0, !switchNode->getValue(0) );
    switchNode->setValue( 1, !switchNode->getValue(1) );
    }
    traverse( node, nv );
}
