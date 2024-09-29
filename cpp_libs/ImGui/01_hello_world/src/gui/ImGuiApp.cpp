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
    drawWindow1();
    drawWindow2();
    drawWindow3();
    drawWindow4();
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

void ImGuiApp::drawWindow1()
{
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

    //ImGui::DockBuilderDockWindow("Window 1", leftDockId());

    if (ImGui::Begin("Window 1"))
    {
        ImGui::Text("This is some useful text.");
    }
    ImGui::End();
}

void ImGuiApp::drawWindow2()
{
    ImGui::SetNextWindowPos(ImVec2(250, 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

    //ImGui::DockBuilderDockWindow("Window 2", rightDockId());

    if (ImGui::Begin("Window 2"))
    {
        ImGui::Text("This is some useful text.");
    }
    ImGui::End();
}

void ImGuiApp::drawWindow3()
{
    ImGui::SetNextWindowPos(ImVec2(250, 250), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

    //ImGui::DockBuilderDockWindow("Window 3", topDockId());

    if (ImGui::Begin("Window 3"))
    {
        ImGui::Text("This is some useful text.");
    }
    ImGui::End();
}

void ImGuiApp::drawWindow4()
{
    ImGui::SetNextWindowPos(ImVec2(50, 250), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

    //ImGui::DockBuilderDockWindow("Window 4", downDockId());

    if (ImGui::Begin("Window 4"))
    {
        ImGui::Text("This is some useful text.");
    }
    ImGui::End();
}

} // namespace gui
} // namespace mc