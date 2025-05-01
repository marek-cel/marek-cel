#include <gui/ImGuiApp.h>

void ImGuiApp::drawUi(osg::RenderInfo& renderInfo)
{
    // Example ImGui UI code
    ImGui::Begin("Example Window");
    ImGui::Text("Hello, world!");
    ImGui::End();
}
