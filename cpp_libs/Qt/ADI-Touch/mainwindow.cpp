#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QCoreApplication>
#include <QtDeclarative/QtDeclarative>

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow ),

    pSensor ( 0 ),
    
    iTimer_ID ( 0 ),
    iPage_Prv ( 0 )
{
    ui->setupUi( this );

    pSensor = new mcel_Sensor();
    
    iTimer_ID = QObject::startTimer( 1000.0 / ADI_TOUCH_FREQ );
    
    pTime = new QTime;
    pTime->start();
    
    ui->qmlView->setSource( QUrl( "qrc:/qml/info.qml" ) );
    
    QDeclarativeContext *pContext = ui->qmlView->rootContext();

    pAction = new QAction( this );
    connect( pAction, SIGNAL(triggered()), SLOT(on_pushBack_clicked()) );

    pContext->setContextProperty( "action", pAction );
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( pTime   ) delete pTime;   pTime   = 0;
    if ( pAction ) delete pAction; pAction = 0;
    if ( pSensor ) delete pSensor; pSensor = 0;

    delete ui;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::setOrientation( ScreenOrientation orientation )
{
#   if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if ( orientation != ScreenOrientationAuto )
    {
        const QStringList v = QString::fromAscii( qVersion() ).split( QLatin1Char('.') );
        if ( v.count() == 3 && ( v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt() ) < 0x040702 )
        {
            qWarning( "Screen orientation locking only supported with Qt 4.7.2 and above" );
            return;
        }
    }
#   endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;

    switch (orientation)
    {
#   if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#   else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#   endif // QT_VERSION < 0x040702
    };

    setAttribute(attribute, true);
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::showExpanded()
{
#   if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    showFullScreen();
#   elif defined(Q_WS_MAEMO_5)
    showMaximized();
#   else
    show();
#   endif
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushBack_clicked()
{
    ui->stackedWidget->setCurrentIndex( 0 );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushExit_clicked()
{
    close();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushInfo_clicked()
{
    ui->stackedWidget->setCurrentIndex( 1 );
    iPage_Prv = 1;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::timerEvent( QTimerEvent *event )
{
    /////////////////////////////
    QObject::timerEvent( event );
    /////////////////////////////
    
    double dDT = pTime->restart();

    pSensor->update();
    
    // if previous page was not home page center ADI widget
    //if ( iPage_Prv != 0 ) ui->adi->centerOn( ui->adi->width()/2.0, ui->adi->height()/2.0 );
    
    // if not hidden update ADI widget
    if ( !isHidden() && ui->stackedWidget->currentIndex() == 0 )
    {
        ui->adi->set( pSensor->getRoll(),
                      pSensor->getPitch() );
    }
    
    // current is now previous
    iPage_Prv = ui->stackedWidget->currentIndex();
}
