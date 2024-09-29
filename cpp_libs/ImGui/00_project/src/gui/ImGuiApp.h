/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
 ******************************************************************************/
#ifndef MC_SIM_GUI_IMGUIAPP_H_
#define MC_SIM_GUI_IMGUIAPP_H_

#include <gui/ImGuiEventHandler.h>

namespace mc {
namespace gui {

class ImGuiApp : public ImGuiEventHandler
{
protected:

    void drawUi(osg::RenderInfo& renderInfo) override;
};

} // namespace gui
} // namespace mc

#endif // MC_SIM_GUI_IMGUIAPP_H_