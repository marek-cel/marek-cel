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

/** This is main window class. */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /** Constructor. */
    explicit MainWindow( QWidget *parent = 0 );

    /** Destructor. */
    virtual ~MainWindow();

protected:

    /** */
    void timerEvent( QTimerEvent *event );

private:

    Ui::MainWindow *_ui;

    int _timerId;                      ///< timer ID

    void settingsRead();
    void settingsSave();
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
