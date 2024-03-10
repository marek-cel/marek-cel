#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QThread>

#include "MyThread.h"

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow() )
{
    _ui->setupUi( this );

    _ui->progressBar->setValue( 0 );

    _myThread = new MyThread( this );

    connect( _myThread, &MyThread::currentCount  , this, &MainWindow::on_currentCount  );
    connect( _myThread, &MyThread::countFinished , this, &MainWindow::on_countFinished );

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
    _myThread->start();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonInfo_clicked()
{
    qDebug() << "Thread is running : " << _myThread->isRunning();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_currentCount(int val)
{
    _ui->progressBar->setValue(val);
    _ui->label->setText( QString::number(val) );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_countFinished()
{
    qDebug() << "Count finished.";
}
