#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QThread>

#include "MyClass.h"

////////////////////////////////////////////////////////////////////////////////

void fun( int count )
{

}

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow() )
{
    _ui->setupUi( this );

    _thread = new QThread( this );

    connect( _thread, &QThread::started, []()
    {
        qDebug() << "Thread started.";
    });

    connect( _thread, &QThread::finished, []()
    {
        qDebug() << "Thread finished.";
    });

    connect( _thread, &QThread::destroyed, []()
    {
        qDebug() << "Thread deleted.";
    });
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
    qDebug() << __func__ << " " << QThread::currentThread();

    MyClass *mc = new MyClass;

    connect( mc, &MyClass::currentCount, this, &MainWindow::on_currentCount );
    connect( mc, &MyClass::countFinished, this, &MainWindow::on_countFinished );

    mc->moveToThread( _thread );

    connect( _thread, &QThread::started, mc, &MyClass::doCount );
    connect( _thread, &QThread::finished, mc, &MyClass::deleteLater );

    _thread->start();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonInfo_clicked()
{
    qDebug() << __func__ << " " << QThread::currentThread();
    qDebug() << _thread->isRunning();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_currentCount(int val)
{
    _ui->progressBar->setValue(val);
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_countFinished()
{
    qDebug() << "Count finished.";
    _thread->exit();
}

