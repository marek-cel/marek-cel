#include <iostream>

#include <QApplication>
#include <QVariant>

#include "MainWindow.h"

////////////////////////////////////////////////////////////////////////////////

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    MainWindow *win = new MainWindow();

    win->show();

    win->setProperty( "var", 1 );

    std::cout << win->getVar() << std::endl;

    return app.exec();
}
