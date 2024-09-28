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
    void drawUi(osg::RenderInfo& renderInfo) override
    {
        // ImGui code goes here...
        ImGui::ShowDemoWindow();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", "CTRL+N")) {}
                if (ImGui::MenuItem("Open", "CTRL+N")) {}
                if (ImGui::MenuItem("Exit", "CTRL+N")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
};

} // namespace gui
} // namespace mc

#endif // MC_SIM_GUI_IMGUIAPP_H_