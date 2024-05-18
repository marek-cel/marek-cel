#pragma once

#include <osgViewer/ViewerEventHandlers>

namespace osg {
class Camera;
}

class OsgImGuiHandler : public osgGA::GUIEventHandler
{
public:
    OsgImGuiHandler();

    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override;

protected:
    // Put your ImGui code inside this function
    virtual void drawUi() = 0;

private:
    void init();

    void setCameraCallbacks(osg::Camera* camera);

    void newFrame(osg::RenderInfo& renderInfo);

    void render(osg::RenderInfo& renderInfo);

private:
    struct ImGuiNewFrameCallback;
    struct ImGuiRenderCallback;

    double _time;
    bool _mousePressed[3];
    float _mouseWheel;
    bool _initialized;
};
