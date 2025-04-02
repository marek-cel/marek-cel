#include <MainWindow.h>
#include <ui_MainWindow.h>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if(_ui) { delete _ui; } _ui = nullptr;
}

void MainWindow::init()
{
    _timer_id = startTimer(1000 / 60); // 60 FPS
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    QMainWindow::timerEvent(event);
}

void MainWindow::on_comboBoxJoysticks_currentIndexChanged(int index)
{
    _joystick_index = index;
}

void MainWindow::on_pushButtonForceX_toggled(bool checked)
{
    std::cout << "Force X: " << (checked ? "ON" : "OFF") << std::endl;

    if ( checked )
    {
        _ui->doubleSpinBoxForceX->setEnabled(true);
        _ui->doubleSpinBoxForceCoefX->setEnabled(true);
        // _joystick.startForcesX();
    }
    else
    {
        _ui->doubleSpinBoxForceX->setValue(0);
        _ui->doubleSpinBoxForceCoefX->setValue(1);
        _ui->doubleSpinBoxForceX->setEnabled(false);
        _ui->doubleSpinBoxForceCoefX->setEnabled(false);
        // _joystick.stopForcesX();
    }
}

void MainWindow::on_pushButtonForceY_toggled(bool checked)
{
    std::cout << "Force Y: " << (checked ? "ON" : "OFF") << std::endl;

    if ( checked )
    {
        _ui->doubleSpinBoxForceY->setEnabled(true);
        _ui->doubleSpinBoxForceCoefY->setEnabled(true);
        // _joystick.startForcesY();
    }
    else
    {
        _ui->doubleSpinBoxForceY->setValue(0);
        _ui->doubleSpinBoxForceCoefY->setValue(1);
        _ui->doubleSpinBoxForceY->setEnabled(false);
        _ui->doubleSpinBoxForceCoefY->setEnabled(false);
        // _joystick.stopForcesY();
    }
}
