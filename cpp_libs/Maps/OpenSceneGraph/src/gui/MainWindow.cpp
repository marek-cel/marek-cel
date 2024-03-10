#include <gui/MainWindow.h>
#include <ui_MainWindow.h>

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow )
{
    _ui->setupUi( this );
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( _ui ) { delete _ui; } _ui = Q_NULLPTR;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_widgetMap_mouseMoveGeoPosition( const QString &str )
{
    _ui->statusBar->showMessage( str );
}
