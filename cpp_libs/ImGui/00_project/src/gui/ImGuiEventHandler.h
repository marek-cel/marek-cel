/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
 ******************************************************************************/
#ifndef MC_SIM_GUI_IMGUIHANDLER_H_
#define MC_SIM_GUI_IMGUIHANDLER_H_

#include <osgGA/GUIEventHandler>

#include <imgui.h>

namespace mc {
namespace gui {

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

} // namespace gui
} // namespace mc

#endif // MC_SIM_GUI_IMGUIHANDLER_H_