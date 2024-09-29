/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
 ******************************************************************************/
#ifndef MC_SIM_GUI_IMGUIHANDLER_H_
#define MC_SIM_GUI_IMGUIHANDLER_H_

#include <osgGA/GUIEventHandler>

#include <imgui.h>

namespace mc {
namespace gui {

class ImGuiEventHandler : public osgGA::GUIEventHandler
{
public:

    ImGuiEventHandler();

    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override;

    void newFrame(osg::RenderInfo& renderInfo);
    void render(osg::RenderInfo& renderInfo);

    void setVisible(bool visible) { _visible = visible; }

    bool visible() const { return _visible; }

    ImGuiID dockSpaceId () const { return _dockSpaceId; }
    // ImGuiID leftDockId  () const { return _leftDockId;  }
    // ImGuiID rightDockId () const { return _rightDockId; }
    // ImGuiID topDockId   () const { return _topDockId;   }
    // ImGuiID downDockId  () const { return _downDockId;  }

protected:

    virtual void initialize();

    // Put your ImGui code inside this function
    virtual void drawUi(osg::RenderInfo& renderInfo) = 0;

private:

    double _time = 0.0;
    bool _initialized = false;
    bool _firstFrame = true;
    bool _visible = true;
    bool _autoAdjustProjMatrix = true;

    ImGuiID _dockSpaceId = 0;
    // ImGuiID _leftDockId  = 0;
    // ImGuiID _rightDockId = 0;
    // ImGuiID _topDockId   = 0;
    // ImGuiID _downDockId  = 0;

    void initializeDockSpace(osg::Viewport* viewport);

    void setCameraCallbacks(osg::Camera* camera);

    ImGuiKey convertKeyToImGui(int osgKey);

    ImGuiButtonFlags convertMouseButtonToImGui(int osgButtonMask);
};

} // namespace gui
} // namespace mc

#endif // MC_SIM_GUI_IMGUIHANDLER_H_