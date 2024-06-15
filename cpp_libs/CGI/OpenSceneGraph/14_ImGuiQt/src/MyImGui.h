#ifndef MYIMGUI_H
#define MYIMGUI_H

#include <imgui/imgui.h>
#include <OsgImGuiHandler.hpp>

class MyImGui : public OsgImGuiHandler
{
protected:

    void drawUi() override
    {
        // ImGui code goes here...
        ImGui::ShowDemoWindow();
    }
};

#endif // MYIMGUI_H
