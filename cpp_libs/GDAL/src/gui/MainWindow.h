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
    explicit MainWindow( QWidget *parent = Q_NULLPTR );

    /** Destructor. */
    virtual ~MainWindow();

private:

    Ui::MainWindow *_ui;

private slots:

    void on_widgetMap_mouseMoveGeoPosition( const QString &str );
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
