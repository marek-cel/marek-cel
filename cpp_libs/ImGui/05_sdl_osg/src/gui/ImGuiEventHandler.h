#ifndef IMGUIEVENTHANDLER_H
#define IMGUIEVENTHANDLER_H

#include <memory>

#include <osgGA/GUIEventHandler>

#include <imgui.h>

class ImGuiEventHandler : public osgGA::GUIEventHandler
{
public:

    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override;

    void newFrame(osg::RenderInfo& renderInfo);
    void render(osg::RenderInfo& renderInfo);

    bool isVisible() const { return _is_visible; }
    void setVisible(bool visible) { _is_visible = visible; }
    void toggleVisible() { _is_visible = !_is_visible; }

protected:

    ImGuiID _dockspace_id = 0;
    bool _initialized = false;
    bool _is_visible = true;
    bool _auto_adjust_proj_matrix = true;

    void setCameraCallbacks(osg::Camera* camera);

    // Put your ImGui code inside this function
    virtual void drawUi(osg::RenderInfo& renderInfo) = 0;
};

#endif // IMGUIEVENTHANDLER_H
