#ifndef CGI_SCENEROOT_H_
#define CGI_SCENEROOT_H_

#include <osg/Group>

class SceneRoot
{
public:
    SceneRoot();
    ~SceneRoot();

    osg::Group* getRootNode() { return _root.get(); }

private:

    osg::ref_ptr<osg::Group> _root;

    void createScene();
};

#endif // CGI_SCENEROOT_H_