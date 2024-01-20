#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QThread>
#include <QThreadPool>

#include "worker.h"

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

void MainWindow::on_pushButtonStart_clicked()
{
    Worker *worker = new Worker();

    QThreadPool::globalInstance()->start( worker );
}

