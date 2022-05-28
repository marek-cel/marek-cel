#include <MainWindow.h>
#include <ui_MainWindow.h>

#include <QSettings>

#include <defs.h>

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow ),
    
    _timerId ( 0 )
{
    _ui->setupUi( this );

    settingsRead();

    _timerId = startTimer( 10 );
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( _timerId ) killTimer( _timerId );

    settingsSave();
    
    if ( _ui ) { delete _ui; } _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::timerEvent( QTimerEvent *event )
{
    /////////////////////////////////
    QMainWindow::timerEvent( event );
    /////////////////////////////////

    _ui->widgetCGI->update();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsRead()
{
    QSettings settings( TEST_ORG_NAME, TEST_APP_NAME );

    settings.beginGroup( "main_window" );

    restoreState( settings.value( "state" ).toByteArray() );
    restoreGeometry( settings.value( "geometry" ).toByteArray() );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsSave()
{
    QSettings settings( TEST_ORG_NAME, TEST_APP_NAME );

    settings.beginGroup( "main_window" );

    settings.setValue( "state", saveState() );
    settings.setValue( "geometry", saveGeometry() );

    settings.endGroup();
}
