#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QThread>

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow() )
{
    _ui->setupUi( this );

    _thread = new MyThread( this );

    connect(_thread,&QThread::started,[]()
    {
        qDebug() << "Thread started. " << QThread::currentThread();
    });

    connect(_thread,&QThread::finished,[]()
    {
        qDebug() << "Thread finished. " << QThread::currentThread();
    });
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    _thread->exit();

    if ( _ui ) delete _ui;
    _ui = nullptr;
}

void MainWindow::on_pushButtonStart_clicked()
{
    _thread->start();
}


void MainWindow::on_pushButtonStop_clicked()
{
    _thread->exit();
}


void MainWindow::on_pushButtonInfo_clicked()
{
    qDebug() << "Thread is running : " << _thread->isRunning();
}

