#ifndef IMGUIEVENTHANDLER_H_
#define IMGUIEVENTHANDLER_H_

#include <osgGA/GUIEventHandler>

#include <imgui.h>

class ImGuiRealizeOperation : public osg::Operation
{
public:
    ImGuiRealizeOperation();
    void operator()(osg::Object* object) override;
};

class ImGuiEventHandler : public osgGA::GUIEventHandler
{
public:

    ImGuiEventHandler();

    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override;

    void newFrame(osg::RenderInfo& renderInfo);
    void render(osg::RenderInfo& renderInfo);

protected:

    // Put your ImGui code inside this function
    virtual void drawUi(osg::RenderInfo& renderInfo) = 0;

private:

    double _time = 0.0;
    bool _initialized = false;
    bool _firstFrame = true;
    bool _show = true;
    bool _autoAdjustProjMatrix = true;

    void setCameraCallbacks(osg::Camera* camera);

    ImGuiKey convertKeyToImGui(int osgKey);

    ImGuiButtonFlags convertMouseButtonToImGui(int osgButtonMask);
};

#endif // IMGUIEVENTHANDLER_H_