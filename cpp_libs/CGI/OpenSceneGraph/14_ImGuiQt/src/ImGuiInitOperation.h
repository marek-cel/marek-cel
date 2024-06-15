#ifndef IMGUIINITOPERATION_H
#define IMGUIINITOPERATION_H

#include <osg/OperationThread>
#include <osg/GraphicsContext>

#include <imgui/backends/imgui_impl_opengl3.h>

class ImGuiInitOperation : public osg::Operation
{
public:
    ImGuiInitOperation()
        : osg::Operation("ImGuiInitOperation", false)
    {
    }

    void operator()(osg::Object* object) override
    {
        osg::GraphicsContext* context = dynamic_cast<osg::GraphicsContext*>(object);
        if (!context)
            return;

        if (!ImGui_ImplOpenGL3_Init())
        {
            std::cout << "ImGui_ImplOpenGL3_Init() failed\n";
        }
    }
};

#endif // IMGUIINITOPERATION_H
