#include <gui/MainWindow.h>
#include <ui_MainWindow.h>

#include <QSettings>

#include <Defines.h>

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    m_ui ( new Ui::MainWindow ),
    m_timerId ( 0 )
{
    m_ui->setupUi( this );

    settingsRead();

    connect( m_ui->widgetMap, SIGNAL( mouseMoveGeoPosition( QString ) ),
                        this, SLOT( widgetMap_mouseMoveGeoPosition( QString ) ) );
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( m_timerId ) killTimer( m_timerId );

    settingsSave();

    if ( m_ui ) delete m_ui;
    m_ui = 0;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::init()
{
    m_timerId = startTimer( GUI_TIME_STEP );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::timerEvent( QTimerEvent *event )
{
    /////////////////////////////////
    QMainWindow::timerEvent( event );
    /////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsRead()
{
    QSettings settings( ORG_NAME, APP_NAME );
    
    settings.beginGroup( "main_window" );

    restoreState( settings.value( "state" ).toByteArray() );
    restoreGeometry( settings.value( "geometry" ).toByteArray() );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsSave()
{
    QSettings settings( ORG_NAME, APP_NAME );
    
    settings.beginGroup( "main_window" );

    settings.setValue( "state", saveState() );
    settings.setValue( "geometry", saveGeometry() );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::widgetMap_mouseMoveGeoPosition( const QString &posStr )
{
    m_ui->statusBar->showMessage( posStr );
}
