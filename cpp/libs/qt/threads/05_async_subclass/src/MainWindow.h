#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>

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

    void on_pushButtonStop_clicked();

    void on_pushButtonInfo_clicked();

private:

    Ui::MainWindow *_ui;

    MyThread *_thread;
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
