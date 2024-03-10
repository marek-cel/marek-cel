#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>
#include <QThread>

#include "MyThread.h"

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

    void on_pushButtonInfo_clicked();

    void on_currentCount(int val );

    void on_countFinished();

private:

    Ui::MainWindow *_ui;

    MyThread *_myThread;
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
