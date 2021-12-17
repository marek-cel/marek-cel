#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QThread>

////////////////////////////////////////////////////////////////////////////////

void fun( int count )
{
    for ( int i = 0; i < count; ++i )
    {
        qDebug() << "func " << i
                  << " " << QThread::currentThread()
                  << " " << QThread::currentThreadId();
    }
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow() )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonChangeLabel_clicked()
{
    static int count = 0;
    count++;
    _ui->label->setText( QString::number( count ) );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonStartLoop_clicked()
{
    //fun( 5e4 );

    QThread *thread = QThread::create( fun, 1e4 );

    connect( thread, &QThread::started, []()
    {
        qDebug() << "Thread started.";
    });

    connect( thread, &QThread::finished, []()
    {
        qDebug() << "Thread finished.";
    });

    connect( thread, &QThread::finished, thread, &QThread::deleteLater );

    connect( thread, &QThread::destroyed, []()
    {
        qDebug() << "Thread deleted.";
    });

    thread->start();
}

