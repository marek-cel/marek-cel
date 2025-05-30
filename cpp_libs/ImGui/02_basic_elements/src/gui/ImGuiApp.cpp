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
    drawMainMenuBar();
    drawWindow();
}

void ImGuiApp::drawMainMenuBar()
{
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

void ImGuiApp::drawWindow()
{
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

    //ImGui::DockBuilderDockWindow("Window 1", leftDockId());

    //if (ImGui::Begin("Window 1", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
    if (ImGui::Begin("Window 1"))
    {
        ImGui::Text("This is some useful text.");

        static bool testBool = true;
        ImGui::Checkbox("Test Checkbox", &testBool);
        if ( testBool )
        {
            ImGui::Text("Checkbox is checked.");
        }
        else
        {
            ImGui::Text("Checkbox is unchecked.");
        }

        if ( ImGui::Button("Test Button") )
        {
            std::cout << "Button pressed." << std::endl;
        }

        static int inttest = 0;
        ImGui::SliderInt("Test Int Slider", &inttest, 0, 100);
        ImGui::Text("Int Slider value: %d", inttest);

        static float floattest = 0.0f;
        ImGui::SliderFloat("Test Float Slider", &floattest, 0.0f, 1.0f);
        ImGui::Text("Float Slider value: %f", floattest);

        ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 50);
        if ( ImGui::Button("Sized Button", ImVec2(100, 50)) )
        {
            std::cout << "Button pressed." << std::endl;
        }
    }
    ImGui::End();
}


} // namespace gui
} // namespace mc