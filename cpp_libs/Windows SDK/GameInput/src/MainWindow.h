#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Controllers.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();

protected:

    void timerEvent(QTimerEvent* event) override;

private:
    Ui::MainWindow* _ui;

    int _timer_id = 0;
    unsigned int _joystick_index = 0;

    Controllers _controllers;

private slots:

    void on_comboBoxJoysticks_currentIndexChanged(int index);
};
#endif // MAINWINDOW_H
