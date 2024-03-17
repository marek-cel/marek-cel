#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

protected:

    void timerEvent(QTimerEvent *event);

private:

    Ui::MainWindow* ui;
    int timerId = 0;
};

#endif // MAINWINDOW_H
