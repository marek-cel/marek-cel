/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
 ******************************************************************************/

#include <gui/ImGuiEventHandler.h>

#include <iostream>

#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include "ImGuiEventHandler.h"

namespace mc {
namespace gui {

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

ImGuiEventHandler::ImGuiEventHandler()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    (void)io;
}

bool ImGuiEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    if (!_initialized)
    {
        osg::View* view = aa.asView();
        if (view)
        {
            setCameraCallbacks(view->getCamera());
            _initialized = true;
            return false;
        }
    }

    if (_firstFrame)
    {
        return false;
    }

    if (ea.getHandled())
    {
        return false;
    }

    ImGuiIO& io = ImGui::GetIO();

    switch ( ea.getEventType() )
    {
    case osgGA::GUIEventAdapter::KEYDOWN:
    case osgGA::GUIEventAdapter::KEYUP:
    {
        const bool isKeyDown = ea.getEventType() == ea.KEYDOWN;
        const int c = ea.getKey();

        if (io.WantCaptureKeyboard || c == ea.KEY_Return)
        {
            // first apply any modifiers:
            io.AddKeyEvent(ImGuiMod_Ctrl  , ( ea.getModKeyMask() & ea.MODKEY_CTRL  ) != 0);
            io.AddKeyEvent(ImGuiMod_Shift , ( ea.getModKeyMask() & ea.MODKEY_SHIFT ) != 0);
            io.AddKeyEvent(ImGuiMod_Alt   , ( ea.getModKeyMask() & ea.MODKEY_ALT   ) != 0);
            io.AddKeyEvent(ImGuiMod_Super , ( ea.getModKeyMask() & ea.MODKEY_SUPER ) != 0);

            // map the OSG key code to the ImGui key code and send to imgui:
            auto imgui_key = convertKeyToImGui(c);
            io.AddKeyEvent(imgui_key, isKeyDown);

            // Send any raw ASCII characters to imgui as input
            if (isKeyDown && c >= 32 && c < 512)
            {
                io.AddInputCharacter((unsigned)c);
            }
        }
        else
        {
            // toggle imgui
            if (isKeyDown && c == 'y')
            {
                _visible = !_visible;
                return true;
            }
        }

        return io.WantCaptureKeyboard;
    }

    case (osgGA::GUIEventAdapter::PUSH):
    {
        if (io.WantCaptureMouse)
        {
            auto imgui_button = convertMouseButtonToImGui(ea.getButtonMask());
            io.AddMousePosEvent(ea.getX(), io.DisplaySize.y - ea.getY());
            io.AddMouseButtonEvent(imgui_button, true); // true = press
        }
        return io.WantCaptureMouse;
    }

    case (osgGA::GUIEventAdapter::RELEASE):
    {
        if (io.WantCaptureMouse)
        {
            io.AddMousePosEvent(ea.getX(), io.DisplaySize.y - ea.getY());
        }
        auto imgui_button = convertMouseButtonToImGui(ea.getButtonMask());
        io.AddMouseButtonEvent(imgui_button, false); // false = release

        return io.WantCaptureMouse;
    }

    case (osgGA::GUIEventAdapter::DRAG):
    case (osgGA::GUIEventAdapter::MOVE):
    {
        io.AddMousePosEvent(ea.getX(), io.DisplaySize.y - ea.getY());
        return io.WantCaptureMouse;
    }

    case (osgGA::GUIEventAdapter::SCROLL):
    {
        auto scrolling = ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP ? 1.0 : -1.0;
        io.AddMouseWheelEvent(0.0, io.MouseWheel += scrolling);
        return io.WantCaptureMouse;
    }
        }

    return false;
}

void ImGuiEventHandler::newFrame(osg::RenderInfo& renderInfo)
{
    if (_firstFrame)
    {
        initialize();
    }

    ImGui_ImplOpenGL3_NewFrame();

    ImGuiIO& io = ImGui::GetIO();

    io.DisplaySize = ImVec2(
        renderInfo.getCurrentCamera()->getGraphicsContext()->getTraits()->width,
        renderInfo.getCurrentCamera()->getGraphicsContext()->getTraits()->height);

    double currentTime = renderInfo.getView()->getFrameStamp()->getSimulationTime();
    io.DeltaTime = currentTime - _time + 0.0000001;
    _time = currentTime;

    if ( _firstFrame )
    {
        _firstFrame = false;
    }

    ImGui::NewFrame();
}

void ImGuiEventHandler::render(osg::RenderInfo& renderInfo)
{
    osg::Camera* camera = renderInfo.getCurrentCamera();
    osg::Viewport* viewport = camera->getViewport();

    if ( _visible )
    {
        constexpr ImGuiDockNodeFlags dockspace_flags =
            ImGuiDockNodeFlags_NoDockingInCentralNode | ImGuiDockNodeFlags_PassthruCentralNode;
        //constexpr ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
        _dockSpaceId = ImGui::GetID("MyDockSpace");
        _dockSpaceId = ImGui::DockSpaceOverViewport(_dockSpaceId, ImGui::GetMainViewport(), dockspace_flags);

        // static bool first_time = true;
        // if (first_time)
        // {
        //     first_time = false;

        //     ImGui::DockBuilderRemoveNode(_dockSpaceId);
        //     ImGui::DockBuilderAddNode(_dockSpaceId, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
        //     ImGui::DockBuilderSetNodeSize(_dockSpaceId, ImVec2(viewport->width(), viewport->height()));

        //     _leftDockId  = ImGui::DockBuilderSplitNode(_dockSpaceId, ImGuiDir_Left  , 0.2f, nullptr, &_dockSpaceId);
        //     _rightDockId = ImGui::DockBuilderSplitNode(_dockSpaceId, ImGuiDir_Right , 0.2f, nullptr, &_dockSpaceId);
        //     _topDockId   = ImGui::DockBuilderSplitNode(_dockSpaceId, ImGuiDir_Up    , 0.2f, nullptr, &_dockSpaceId);
        //     _downDockId  = ImGui::DockBuilderSplitNode(_dockSpaceId, ImGuiDir_Down  , 0.2f, nullptr, &_dockSpaceId);

        //     ImGui::DockBuilderFinish(_dockSpaceId);
        // }

        glDisable(GL_MULTISAMPLE);

        drawUi(renderInfo);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiDockNode* centralNode = ImGui::DockBuilderGetCentralNode(_dockSpaceId);

        auto io = ImGui::GetIO();
        viewport->x() = centralNode->Pos.x;
        viewport->y() = io.DisplaySize.y - centralNode->Size.y - centralNode->Pos.y;
        viewport->width() = centralNode->Size.x;
        viewport->height() = centralNode->Size.y;
    }
    else
    {
        viewport->x() = 0;
        viewport->y() = 0;
        viewport->width() = camera->getGraphicsContext()->getTraits()->width;
        viewport->height() = camera->getGraphicsContext()->getTraits()->height;
        ImGui::EndFrame();
    }

    if ( _autoAdjustProjMatrix )
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

void ImGuiEventHandler::initialize()
{
    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void ImGuiEventHandler::setCameraCallbacks(osg::Camera *camera)
{
    camera->setPreDrawCallback(new PreDrawOp(*this));
    camera->setPostDrawCallback(new PostDrawOp(*this));
}

ImGuiKey ImGuiEventHandler::convertKeyToImGui(int osgKey)
{
    // If you are holding CTRL, OSG remaps A-Z to 1-26. Undo that.
    if ( osgKey >= 1 && osgKey <= 26 )
    {
        return static_cast<ImGuiKey>(static_cast<int>(ImGuiKey_A) + osgKey - 1);
    }

    if ( osgKey >= osgGA::GUIEventAdapter::KEY_0 && osgKey <= osgGA::GUIEventAdapter::KEY_0 )
    {
        return static_cast<ImGuiKey>(static_cast<int>(ImGuiKey_0) + osgKey - osgGA::GUIEventAdapter::KEY_0);
    }

    if ( osgKey >= osgGA::GUIEventAdapter::KEY_A && osgKey <= osgGA::GUIEventAdapter::KEY_Z )
    {
        return static_cast<ImGuiKey>(static_cast<int>(ImGuiKey_A) + osgKey - osgGA::GUIEventAdapter::KEY_A);
    }

    switch ( osgKey )
    {
    case osgGA::GUIEventAdapter::KEY_Tab:
        return ImGuiKey_Tab;
    case osgGA::GUIEventAdapter::KEY_Left:
        return ImGuiKey_LeftArrow;
    case osgGA::GUIEventAdapter::KEY_Right:
        return ImGuiKey_RightArrow;
    case osgGA::GUIEventAdapter::KEY_Up:
        return ImGuiKey_UpArrow;
    case osgGA::GUIEventAdapter::KEY_Down:
        return ImGuiKey_DownArrow;
    case osgGA::GUIEventAdapter::KEY_Page_Up:
        return ImGuiKey_PageUp;
    case osgGA::GUIEventAdapter::KEY_Page_Down:
        return ImGuiKey_PageDown;
    case osgGA::GUIEventAdapter::KEY_Home:
        return ImGuiKey_Home;
    case osgGA::GUIEventAdapter::KEY_End:
        return ImGuiKey_End;
    case osgGA::GUIEventAdapter::KEY_Delete:
        return ImGuiKey_Delete;
    case osgGA::GUIEventAdapter::KEY_BackSpace:
        return ImGuiKey_Backspace;
    case osgGA::GUIEventAdapter::KEY_Return:
        return ImGuiKey_Enter;
    case osgGA::GUIEventAdapter::KEY_Escape:
        return ImGuiKey_Escape;
    case osgGA::GUIEventAdapter::KEY_Space:
        return ImGuiKey_Space;
    }

    return ImGuiKey_None;
}

ImGuiButtonFlags ImGuiEventHandler::convertMouseButtonToImGui(int osgButtonMask)
{
    ImGuiButtonFlags flags = 0;
    if ( osgButtonMask & osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON )
    {
        flags |= ImGuiMouseButton_Left;
    }

    if ( osgButtonMask & osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON )
    {
        flags |= ImGuiMouseButton_Right;
    }

    if ( osgButtonMask & osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON )
    {
        flags |= ImGuiMouseButton_Middle;
    }

    return flags;
}

} // namespace gui
} // namespace mc