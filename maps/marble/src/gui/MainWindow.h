#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class MainWindow;
}

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Main window class.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /** Constructor. */
    explicit MainWindow( QWidget *parent = 0 );

    /** Destructor. */
    virtual ~MainWindow();

    /** */
    void init();

protected:

    /** */
    void timerEvent( QTimerEvent *event );

private:

    Ui::MainWindow *m_ui;

    int m_timerId;                  ///< timer ID

    void settingsRead();
    void settingsSave();

private slots:

    void widgetMap_mouseMoveGeoPosition( const QString &posStr );

};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
