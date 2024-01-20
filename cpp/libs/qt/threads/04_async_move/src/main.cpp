#include <QApplication>
#include <QDebug>
#include <QThread>

#include "MainWindow.h"

////////////////////////////////////////////////////////////////////////////////

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    MainWindow w;

    w.show();

    qDebug() << QThread::currentThread() << " " << QThread::currentThreadId();

    return a.exec();
}
