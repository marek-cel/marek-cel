/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
 ******************************************************************************/

#include <gui/ImGuiApp.h>

#include <iostream>

#include <imgui_internal.h>

namespace mc {
namespace gui {

void ImGuiApp::drawUi(osg::RenderInfo& renderInfo)
{
    ImGui::ShowDemoWindow();
}


} // namespace gui
} // namespace mc