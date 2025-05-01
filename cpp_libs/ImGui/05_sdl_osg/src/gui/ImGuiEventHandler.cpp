#include <gui/ImGuiEventHandler.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>
#include <imgui_internal.h>

struct PreDrawOp : public osg::Camera::DrawCallback
{
    ImGuiEventHandler& _handler;
    PreDrawOp(ImGuiEventHandler& handler) : _handler(handler) {}
    void operator()(osg::RenderInfo& renderInfo) const override
    {
        _handler.newFrame(renderInfo);
    }
};

struct PostDrawOp : public osg::Camera::DrawCallback
{
    ImGuiEventHandler& _handler;
    PostDrawOp(ImGuiEventHandler& handler) : _handler(handler) {}
    void operator()(osg::RenderInfo& renderInfo) const override
    {
        _handler.render(renderInfo);
    }
};

bool ImGuiEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    if ( !_initialized )
    {
        osg::View* view = aa.asView();
        if (view)
        {
            setCameraCallbacks(view->getCamera());
            _initialized = true;
            return false;
        }
    }

    if (ea.getHandled())
    {
        return false;
    }

    return false;
}

void ImGuiEventHandler::newFrame(osg::RenderInfo& renderInfo)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();

    ImGuiIO& io = ImGui::GetIO();

    io.DisplaySize = ImVec2(renderInfo.getCurrentCamera()->getGraphicsContext()->getTraits()->width,
                            renderInfo.getCurrentCamera()->getGraphicsContext()->getTraits()->height);

    ImGui::NewFrame();
}

void ImGuiEventHandler::render(osg::RenderInfo& renderInfo)
{
    osg::Camera* camera = renderInfo.getCurrentCamera();
    osg::Viewport* viewport = camera->getViewport();

    if ( _is_visible )
    {
        constexpr ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_NoDockingInCentralNode
                                                     | ImGuiDockNodeFlags_PassthruCentralNode;
        _dockspace_id = ImGui::GetID("MyDockSpace");
        _dockspace_id = ImGui::DockSpaceOverViewport(_dockspace_id, ImGui::GetMainViewport(), dockspace_flags);

        // glDisable(GL_MULTISAMPLE);

        drawUi(renderInfo);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiDockNode* central_node = ImGui::DockBuilderGetCentralNode(_dockspace_id);

        auto io = ImGui::GetIO();
        if (central_node)
        {
            viewport->x() = central_node->Pos.x;
            viewport->y() = io.DisplaySize.y - central_node->Size.y - central_node->Pos.y;
            viewport->width() = central_node->Size.x;
            viewport->height() = central_node->Size.y;
        }
    }
    else
    {
        viewport->x() = 0;
        viewport->y() = 0;
        viewport->width() = camera->getGraphicsContext()->getTraits()->width;
        viewport->height() = camera->getGraphicsContext()->getTraits()->height;
        ImGui::EndFrame();
    }

    if ( _auto_adjust_proj_matrix )
    {
        const osg::Matrixd& proj = camera->getProjectionMatrix();
        bool isOrtho = osg::equivalent(proj(3, 3), 1.0);
        if (!isOrtho)
        {
            double fovy, ar, znear, zfar;
            camera->getProjectionMatrixAsPerspective(fovy, ar, znear, zfar);
            camera->setProjectionMatrixAsPerspective(fovy, viewport->width() / viewport->height(), znear, zfar);
        }
        else
        {
            double left, right, bottom, top, znear, zfar;
            camera->getProjectionMatrixAsOrtho(left, right, bottom, top, znear, zfar);
            camera->setProjectionMatrixAsOrtho(viewport->x(), viewport->x() + viewport->width(), viewport->y(), viewport->y() + viewport->height(), znear, zfar);
        }
    }
}

void ImGuiEventHandler::setCameraCallbacks(osg::Camera* camera)
{
    camera->setPreDrawCallback(new PreDrawOp(*this));
    camera->setPostDrawCallback(new PostDrawOp(*this));
}
