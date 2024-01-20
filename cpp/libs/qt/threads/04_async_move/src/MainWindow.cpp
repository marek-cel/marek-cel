#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QTimer>
#include <QThread>

#include "Worker.h"

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow() )
{
    _ui->setupUi( this );

    _thread = new QThread( this );
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonStart_clicked()
{
    Worker *worker = new Worker();

    worker->moveToThread( _thread );

    connect(_thread,&QThread::started,worker,&Worker::doWork );

    connect(_thread,&QThread::started,[]()
    {
        qDebug() << "Thread started.";
    });

    connect(_thread,&QThread::finished,[]()
    {
        qDebug() << "Thread finished.";
    });

    connect(_thread,&QThread::finished,[&]()
    {
        worker->deleteLater();
    });

    _thread->start();
}


void MainWindow::on_pushButtonStop_clicked()
{
    _thread->exit();
}

