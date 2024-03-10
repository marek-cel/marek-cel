#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

////////////////////////////////////////////////////////////////////////////////

#include <QTime>
#include <QtGui/QMainWindow>

#include "mcel_sensor.h"

////////////////////////////////////////////////////////////////////////////////

#define ADI_TOUCH_FREQ 25.0

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
class MainWindow;
}

////////////////////////////////////////////////////////////////////////////////

/** @author Marek Cel (mcel@mcel.pl) */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    enum ScreenOrientation
    {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

private:

    Ui::MainWindow  *ui;        ///<

    QAction         *pAction;   ///<
    QTime           *pTime;     ///<

    mcel_Sensor     *pSensor;   ///<
    
    int     iTimer_ID;          ///<
    int     iPage_Prv;          ///<

public:

    /** */
    explicit MainWindow( QWidget *parent = 0 );

    /** */
    virtual ~MainWindow();

    /** Note that this will only have an effect on Symbian and Fremantle. */
    void setOrientation( ScreenOrientation orientation );

    /** */
    void showExpanded();

private slots:

    /** */
    void on_pushBack_clicked();
    
    /** */
    void on_pushExit_clicked();

    /** */
    void on_pushInfo_clicked();
       
private:

    /** */
    void timerEvent( QTimerEvent *event );
};

////////////////////////////////////////////////////////////////////////////////

#endif // _MAINWINDOW_H_
