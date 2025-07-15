#include <iostream>

#include <QApplication>

#include <QVTKOpenGLNativeWidget.h>

#include <defs.h>
#include <MainWindow.h>

int main(int argc, char* argv[])
{
    // needed to ensure appropriate OpenGL context is created for VTK rendering.
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    QApplication app(argc, argv);
    app.setApplicationName    ( APP_NAME   );
    app.setApplicationVersion ( APP_VER    );
    app.setOrganizationDomain ( ORG_DOMAIN );
    app.setOrganizationName   ( ORG_NAME   );
    MainWindow win;
    win.show();
    return app.exec();
}