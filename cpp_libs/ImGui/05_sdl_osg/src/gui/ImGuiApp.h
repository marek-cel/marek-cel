#ifndef IMGUIAPP_H
#define IMGUIAPP_H

#include <gui/ImGuiEventHandler.h>

class ImGuiApp : public ImGuiEventHandler
{
public:

protected:

    void drawUi(osg::RenderInfo& renderInfo) override;
};

#endif // IMGUIAPP_H
