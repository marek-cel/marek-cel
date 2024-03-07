#include <MainWindow.h>
#include <ui_MainWindow.h>

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    m_ui ( new Ui::MainWindow ),
    
    m_timerId ( 0 )
{
    m_ui->setupUi( this );

    m_timerId = startTimer(17);
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( m_timerId ) killTimer( m_timerId );
    
    if ( m_ui ) { delete m_ui; } m_ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::timerEvent( QTimerEvent *event )
{
    /////////////////////////////////
    QMainWindow::timerEvent( event );
    /////////////////////////////////

    m_ui->widgetCGI->update();
}
