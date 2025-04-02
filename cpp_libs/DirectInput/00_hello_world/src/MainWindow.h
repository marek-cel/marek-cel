#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Joystick.h>

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
    int _joystick_index = 0;

    Joystick _joystick;

private slots:

    void on_comboBoxJoysticks_currentIndexChanged(int index);
    void on_pushButtonForceX_toggled(bool checked);
    void on_pushButtonForceY_toggled(bool checked);
};
#endif // MAINWINDOW_H
