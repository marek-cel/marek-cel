#include "mainwindow.h"

#include <QtGui/QApplication>

////////////////////////////////////////////////////////////////////////////////

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    MainWindow   win;
    
    win.setOrientation( MainWindow::ScreenOrientationLockLandscape );
    win.showExpanded();

    return app.exec();
}
