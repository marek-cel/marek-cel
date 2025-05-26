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
    WId WinID = effectiveWinId();

    // _joystick.init((HWND)WinID);
    // Joystick::Data* data = Joystick::getData();
    // for (auto& joy_data : data->joys)
    // {
    //     _ui->comboBoxJoysticks->addItem(QString::fromStdString(joy_data.name));
    // }

    _joys = new MSc_Joys((void*)&WinID);
    int joy_count = _joys->getJoyCount();
    for (int i = 0; i < joy_count; ++i)
    {
        MSc_JoyData joy_data;
        _joys->getJoyData(i, joy_data);
        _ui->comboBoxJoysticks->addItem(QString::fromStdString(joy_data.acName));
    }

    _timer_id = startTimer(1000 / 60); // 60 FPS
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    QMainWindow::timerEvent(event);

    // _joystick.update();
    // Joystick::Data* data = Joystick::getData();

    // if (_joystick_index < data->joys.size())
    // {
    //     Joystick::Data::Joystick& joy_data = data->joys[_joystick_index];

    //     _ui->spinBoxX->setValue(joy_data.axes[0]);
    //     _ui->spinBoxY->setValue(joy_data.axes[1]);
    //     _ui->spinBoxZ->setValue(joy_data.axes[2]);
    //     _ui->spinBoxRX->setValue(joy_data.axes[3]);
    //     _ui->spinBoxRY->setValue(joy_data.axes[4]);
    //     _ui->spinBoxRZ->setValue(joy_data.axes[5]);
    //     _ui->spinBoxSlider1->setValue(joy_data.axes[6]);
    //     _ui->spinBoxSlider2->setValue(joy_data.axes[7]);

    //     _ui->pushButton_1->setChecked(joy_data.buttons[0]);
    //     _ui->pushButton_2->setChecked(joy_data.buttons[1]);
    //     _ui->pushButton_3->setChecked(joy_data.buttons[2]);
    //     _ui->pushButton_4->setChecked(joy_data.buttons[3]);
    //     _ui->pushButton_5->setChecked(joy_data.buttons[4]);
    //     _ui->pushButton_6->setChecked(joy_data.buttons[5]);
    //     _ui->pushButton_7->setChecked(joy_data.buttons[6]);
    //     _ui->pushButton_8->setChecked(joy_data.buttons[7]);
    //     _ui->pushButton_9->setChecked(joy_data.buttons[8]);
    //     _ui->pushButton_10->setChecked(joy_data.buttons[9]);
    //     _ui->pushButton_11->setChecked(joy_data.buttons[10]);
    //     _ui->pushButton_12->setChecked(joy_data.buttons[11]);
    //     _ui->pushButton_13->setChecked(joy_data.buttons[12]);
    //     _ui->pushButton_14->setChecked(joy_data.buttons[13]);
    //     _ui->pushButton_15->setChecked(joy_data.buttons[14]);
    //     _ui->pushButton_16->setChecked(joy_data.buttons[15]);
    //     _ui->pushButton_17->setChecked(joy_data.buttons[16]);
    //     _ui->pushButton_18->setChecked(joy_data.buttons[17]);
    //     _ui->pushButton_19->setChecked(joy_data.buttons[18]);
    //     _ui->pushButton_20->setChecked(joy_data.buttons[19]);
    //     _ui->pushButton_21->setChecked(joy_data.buttons[20]);
    //     _ui->pushButton_22->setChecked(joy_data.buttons[21]);
    //     _ui->pushButton_23->setChecked(joy_data.buttons[22]);
    //     _ui->pushButton_24->setChecked(joy_data.buttons[23]);
    //     _ui->pushButton_25->setChecked(joy_data.buttons[24]);
    //     _ui->pushButton_26->setChecked(joy_data.buttons[25]);
    //     _ui->pushButton_27->setChecked(joy_data.buttons[26]);
    //     _ui->pushButton_28->setChecked(joy_data.buttons[27]);
    //     _ui->pushButton_29->setChecked(joy_data.buttons[28]);
    //     _ui->pushButton_30->setChecked(joy_data.buttons[29]);
    //     _ui->pushButton_31->setChecked(joy_data.buttons[30]);
    //     _ui->pushButton_32->setChecked(joy_data.buttons[31]);

    //     if (joy_data.force_feedback)
    //     {
    //         _ui->groupBoxForceFeedback->setEnabled(true);

    //         if ( _ui->pushButtonForceX->isChecked() )
    //         {
    //             joy_data.magnitude_x = _ui->doubleSpinBoxForceX->value() * _ui->doubleSpinBoxForceCoefX->value();
    //         }
    //         else
    //         {
    //             joy_data.magnitude_x = 0.0;
    //         }

    //         if ( _ui->pushButtonForceY->isChecked() )
    //         {
    //             joy_data.magnitude_y = _ui->doubleSpinBoxForceY->value() * _ui->doubleSpinBoxForceCoefY->value();
    //         }
    //         else
    //         {
    //             joy_data.magnitude_y = 0.0;
    //         }
    //     }
    //     else
    //     {
    //         _ui->groupBoxForceFeedback->setEnabled(false);
    //         _ui->pushButtonForceX->setChecked(false);
    //         _ui->pushButtonForceY->setChecked(false);

    //         joy_data.magnitude_x = 0.0;
    //         joy_data.magnitude_y = 0.0;
    //     }
    // }

    _joys->update();
    if ( _joystick_index < _joys->getJoyCount() )
    {
        MSc_JoyData joy_data;
        _joys->getJoyData(_joystick_index, joy_data);

        _ui->spinBoxX->setValue(joy_data.dAxis[0]);
        _ui->spinBoxY->setValue(joy_data.dAxis[1]);
        _ui->spinBoxZ->setValue(joy_data.dAxis[2]);
        _ui->spinBoxRX->setValue(joy_data.dAxis[3]);
        _ui->spinBoxRY->setValue(joy_data.dAxis[4]);
        _ui->spinBoxRZ->setValue(joy_data.dAxis[5]);
        _ui->spinBoxSlider1->setValue(joy_data.dAxis[6]);
        _ui->spinBoxSlider2->setValue(joy_data.dAxis[7]);

        _ui->pushButton_1->setChecked(joy_data.iButt[0]);
        _ui->pushButton_2->setChecked(joy_data.iButt[1]);
        _ui->pushButton_3->setChecked(joy_data.iButt[2]);
        _ui->pushButton_4->setChecked(joy_data.iButt[3]);
        _ui->pushButton_5->setChecked(joy_data.iButt[4]);
        _ui->pushButton_6->setChecked(joy_data.iButt[5]);
        _ui->pushButton_7->setChecked(joy_data.iButt[6]);
        _ui->pushButton_8->setChecked(joy_data.iButt[7]);
        _ui->pushButton_9->setChecked(joy_data.iButt[8]);
        _ui->pushButton_10->setChecked(joy_data.iButt[9]);
        _ui->pushButton_11->setChecked(joy_data.iButt[10]);
        _ui->pushButton_12->setChecked(joy_data.iButt[11]);
        _ui->pushButton_13->setChecked(joy_data.iButt[12]);
        _ui->pushButton_14->setChecked(joy_data.iButt[13]);
        _ui->pushButton_15->setChecked(joy_data.iButt[14]);
        _ui->pushButton_16->setChecked(joy_data.iButt[15]);
        _ui->pushButton_17->setChecked(joy_data.iButt[16]);
        _ui->pushButton_18->setChecked(joy_data.iButt[17]);
        _ui->pushButton_19->setChecked(joy_data.iButt[18]);
        _ui->pushButton_20->setChecked(joy_data.iButt[19]);
        _ui->pushButton_21->setChecked(joy_data.iButt[20]);
        _ui->pushButton_22->setChecked(joy_data.iButt[21]);
        _ui->pushButton_23->setChecked(joy_data.iButt[22]);
        _ui->pushButton_24->setChecked(joy_data.iButt[23]);
        _ui->pushButton_25->setChecked(joy_data.iButt[24]);
        _ui->pushButton_26->setChecked(joy_data.iButt[25]);
        _ui->pushButton_27->setChecked(joy_data.iButt[26]);
        _ui->pushButton_28->setChecked(joy_data.iButt[27]);
        _ui->pushButton_29->setChecked(joy_data.iButt[28]);
        _ui->pushButton_30->setChecked(joy_data.iButt[29]);
        _ui->pushButton_31->setChecked(joy_data.iButt[30]);
        _ui->pushButton_32->setChecked(joy_data.iButt[31]);

        if ( joy_data.iForce )
        {
            _ui->groupBoxForceFeedback->setEnabled(true);
            _ui->pushButtonForce->setEnabled(true);
            if ( _ui->pushButtonForce->isChecked() )
            {
                double forceX = _ui->doubleSpinBoxForceX->value() * _ui->doubleSpinBoxForceCoefX->value();
                double forceY = _ui->doubleSpinBoxForceY->value() * _ui->doubleSpinBoxForceCoefY->value();
                _joys->setForceX(_joystick_index, forceX);
                _joys->setForceY(_joystick_index, forceY);
            }
            else
            {
                _joys->setForceX(_joystick_index, 0);
                _joys->setForceY(_joystick_index, 0);
            }
        }
        else
        {
            _ui->groupBoxForceFeedback->setEnabled(false);
            _ui->pushButtonForce->setChecked(false);
        }
    }
}

void MainWindow::on_comboBoxJoysticks_currentIndexChanged(int index)
{
    _joystick_index = index;
}

void MainWindow::on_pushButtonForce_toggled(bool checked)
{
    std::cout << "Force: " << (checked ? "ON" : "OFF") << std::endl;

    // if ( checked )
    // {
    //     _ui->doubleSpinBoxForceX->setEnabled(true);
    //     _ui->doubleSpinBoxForceCoefX->setEnabled(true);
    //     _joystick.startForcesX();
    // }
    // else
    // {
    //     _ui->doubleSpinBoxForceX->setValue(0);
    //     _ui->doubleSpinBoxForceCoefX->setValue(1);
    //     _ui->doubleSpinBoxForceX->setEnabled(false);
    //     _ui->doubleSpinBoxForceCoefX->setEnabled(false);
    //     _joystick.stopForcesX();
    // }

    if ( checked )
    {
        _ui->doubleSpinBoxForceX->setEnabled(true);
        _ui->doubleSpinBoxForceY->setEnabled(true);
        _ui->doubleSpinBoxForceCoefX->setEnabled(true);
        _ui->doubleSpinBoxForceCoefY->setEnabled(true);
        _joys->startForces();
    }
    else
    {
        _ui->doubleSpinBoxForceX->setValue(0);
        _ui->doubleSpinBoxForceY->setValue(0);
        _ui->doubleSpinBoxForceCoefX->setValue(1);
        _ui->doubleSpinBoxForceCoefY->setValue(1);
        _ui->doubleSpinBoxForceX->setEnabled(false);
        _ui->doubleSpinBoxForceY->setEnabled(false);
        _ui->doubleSpinBoxForceCoefX->setEnabled(false);
        _ui->doubleSpinBoxForceCoefY->setEnabled(false);
        _joys->stopForces();
    }
}
