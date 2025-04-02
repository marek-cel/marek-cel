#include <memory>

#include <QApplication>

#include <MainWindow.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow win;
    win.show();
    win.init();

    int result = app.exec();

    return result;
}
