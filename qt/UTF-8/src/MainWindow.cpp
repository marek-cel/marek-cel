#include "MainWindow.h"
#include "ui_MainWindow.h"

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow() )
{
    _ui->setupUi( this );

    QString text = u8"Za\305\274\303\263\305\202\304\207 g\304\231\305\233l\304\205 ja\305\272\305\204";

    _ui->label->setText( text );
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}
