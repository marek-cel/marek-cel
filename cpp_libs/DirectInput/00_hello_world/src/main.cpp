#include <memory>

#include <QApplication>

#include <gui/MainWindow.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow win;
    win.show();

    int result = app.exec();

    return result;
}
