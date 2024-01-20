#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow() )
{
    _ui->setupUi( this );

    _ui->progressBar_1->setValue( 0 );
    _ui->progressBar_2->setValue( 0 );

    _mythreadLoop = new MyThreadLoop( this );

    connect( _mythreadLoop, &MyThreadLoop::started, []()
    {
        qDebug() << "MyThreadLoop started " << QThread::currentThread();
    });

    connect( _mythreadLoop, &MyThreadLoop::finished, []()
    {
        qDebug() << "MyThreadLoop finished " << QThread::currentThread();
    });

    connect( _mythreadLoop, &MyThreadLoop::currentCount  , this, &MainWindow::on_currentCountLoop  );
    connect( _mythreadLoop, &MyThreadLoop::countFinished , this, &MainWindow::on_countFinishedLoop );

    _mythreadTimer = new MyThreadTimer( 100, this );

    connect( _mythreadTimer, &MyThreadTimer::started, []()
    {
        qDebug() << "MyThreadTimer started " << QThread::currentThread();
    });

    connect( _mythreadTimer, &MyThreadTimer::finished, []()
    {
        qDebug() << "MyThreadTimer finished " << QThread::currentThread();
    });

    connect( _mythreadTimer, &MyThreadTimer::currentCount  , this, &MainWindow::on_currentCountTimer  );
    connect( _mythreadTimer, &MyThreadTimer::countFinished , this, &MainWindow::on_countFinishedTimer );
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    qDebug() << __func__ << " " << QThread::currentThread();

    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonStart_clicked()
{
    qDebug() << __func__ << " " << QThread::currentThread();
    _mythreadLoop  ->start();
    _mythreadTimer ->start();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonStop_clicked()
{
    qDebug() << __func__ << " " << QThread::currentThread();
    _mythreadLoop  ->exit();
    _mythreadTimer ->exit();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonInfo_clicked()
{
    qDebug() << __func__ << " " << QThread::currentThread();
    qDebug() << "MyThreadLoop is running : "  << _mythreadLoop  ->isRunning();
    qDebug() << "MyThreadTimer is running : " << _mythreadTimer ->isRunning();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_currentCountLoop(int count)
{
    _ui->progressBar_1->setValue( count );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_countFinishedLoop()
{
    qDebug() << __func__ << " " << QThread::currentThread();
    _mythreadLoop  ->exit();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_currentCountTimer(int count)
{
    _ui->progressBar_2->setValue( count );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_countFinishedTimer()
{
    qDebug() << __func__ << " " << QThread::currentThread();
    _mythreadTimer ->exit();
}

