/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
 ******************************************************************************/
#ifndef IMGUIAPP_H_
#define IMGUIAPP_H_

#include <ImGuiEventHandler.h>

class ImGuiApp : public ImGuiEventHandler
{
protected:

    void drawUi(osg::RenderInfo& renderInfo) override;

private:

    void drawMainMenuBar();
    void drawWindow1();
    void drawWindow2();
};

#endif // IMGUIAPP_H_