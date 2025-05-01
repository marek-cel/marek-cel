#include <gui/ImGuiApp.h>

#include <imgui.h>

void ImGuiApp::drawUi(osg::RenderInfo& renderInfo)
{
    ImGui::Begin("Example Window");
    ImGui::Text("Hello, world!");
    ImGui::End();

    ImGui::ShowDemoWindow();
}
