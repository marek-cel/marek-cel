#include <QApplication>
#include <gui/Widget.h>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    Widget gui;

    gui.show();

    return app.exec();
}
