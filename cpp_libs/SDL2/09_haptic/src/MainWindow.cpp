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
    _controllers.init();

    auto controllers = _controllers.getControllers();
    for ( const auto& controller : controllers )
    {
        _ui->comboBoxJoysticks->addItem(QString::fromStdString(controller.name));
    }

    _timer_id = startTimer(1000 / 60); // 60 FPS
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    QMainWindow::timerEvent(event);

    _controllers.update();

    auto controllers = _controllers.getControllers();
    if ( _joystick_index < controllers.size() )
    {
        auto& controller = controllers[_joystick_index];

        _ui->spinBoxX->setValue(controller.axes[0]);
        _ui->spinBoxY->setValue(controller.axes[1]);
        _ui->spinBoxZ->setValue(controller.axes[2]);
        _ui->spinBoxRX->setValue(controller.axes[3]);
        _ui->spinBoxRY->setValue(controller.axes[4]);
        _ui->spinBoxRZ->setValue(controller.axes[5]);
        _ui->spinBoxSlider1->setValue(controller.axes[6]);
        _ui->spinBoxSlider2->setValue(controller.axes[7]);

        _ui->pushButton_1->setChecked(controller.buttons[0]);
        _ui->pushButton_2->setChecked(controller.buttons[1]);
        _ui->pushButton_3->setChecked(controller.buttons[2]);
        _ui->pushButton_4->setChecked(controller.buttons[3]);
        _ui->pushButton_5->setChecked(controller.buttons[4]);
        _ui->pushButton_6->setChecked(controller.buttons[5]);
        _ui->pushButton_7->setChecked(controller.buttons[6]);
        _ui->pushButton_8->setChecked(controller.buttons[7]);
        _ui->pushButton_9->setChecked(controller.buttons[8]);
        _ui->pushButton_10->setChecked(controller.buttons[9]);
        _ui->pushButton_11->setChecked(controller.buttons[10]);
        _ui->pushButton_12->setChecked(controller.buttons[11]);
        _ui->pushButton_13->setChecked(controller.buttons[12]);
        _ui->pushButton_14->setChecked(controller.buttons[13]);
        _ui->pushButton_15->setChecked(controller.buttons[14]);
        _ui->pushButton_16->setChecked(controller.buttons[15]);
        _ui->pushButton_17->setChecked(controller.buttons[16]);
        _ui->pushButton_18->setChecked(controller.buttons[17]);
        _ui->pushButton_19->setChecked(controller.buttons[18]);
        _ui->pushButton_20->setChecked(controller.buttons[19]);
        _ui->pushButton_21->setChecked(controller.buttons[20]);
        _ui->pushButton_22->setChecked(controller.buttons[21]);
        _ui->pushButton_23->setChecked(controller.buttons[22]);
        _ui->pushButton_24->setChecked(controller.buttons[23]);
        _ui->pushButton_25->setChecked(controller.buttons[24]);
        _ui->pushButton_26->setChecked(controller.buttons[25]);
        _ui->pushButton_27->setChecked(controller.buttons[26]);
        _ui->pushButton_28->setChecked(controller.buttons[27]);
        _ui->pushButton_29->setChecked(controller.buttons[28]);
        _ui->pushButton_30->setChecked(controller.buttons[29]);
        _ui->pushButton_31->setChecked(controller.buttons[30]);
        _ui->pushButton_32->setChecked(controller.buttons[31]);

        _controllers.updateConstantForce(_joystick_index,
                                        _ui->doubleSpinBoxForceX->value(),
                                        _ui->doubleSpinBoxForceY->value());
    }
}

void MainWindow::on_comboBoxJoysticks_currentIndexChanged(int index)
{
    _joystick_index = index;
}

void MainWindow::on_pushButtonStartConstForce_toggled(bool checked)
{
    std::cout << "Force X: " << (checked ? "ON" : "OFF") << std::endl;

    if ( checked )
    {
        _ui->doubleSpinBoxForceX->setEnabled(true);
        _ui->doubleSpinBoxForceY->setEnabled(true);
        _controllers.startConstantForce(_joystick_index);
    }
    else
    {
        _ui->doubleSpinBoxForceX->setValue(0);
        _ui->doubleSpinBoxForceY->setValue(0);
        _ui->doubleSpinBoxForceX->setEnabled(false);
        _ui->doubleSpinBoxForceY->setEnabled(false);
        _controllers.stopAllEffects();
    }
}

