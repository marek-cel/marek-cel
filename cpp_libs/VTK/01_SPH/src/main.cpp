#include <iostream>

#include <QApplication>

#include <Widget.h>

int main(int argc, char* argv[])
{
    // needed to ensure appropriate OpenGL context is created for VTK rendering.
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    QApplication app(argc, argv);
    Widget widget;
    widget.show();
    return app.exec();
}