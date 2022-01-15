#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>

#include "MyThreadLoop.h"
#include "MyThreadTimer.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class MainWindow;
}

////////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow( QWidget *parent = nullptr );

    ~MainWindow();

private slots:

    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonInfo_clicked();

    void on_currentCountLoop( int count );
    void on_countFinishedLoop();

    void on_currentCountTimer( int count );
    void on_countFinishedTimer();

private:

    Ui::MainWindow *_ui;

    MyThreadLoop *_mythreadLoop;
    MyThreadTimer *_mythreadTimer;
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
