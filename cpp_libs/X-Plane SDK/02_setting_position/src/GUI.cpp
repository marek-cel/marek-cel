#include "GUI.h"
#include "ui_GUI.h"

#include <iostream>

#include <QDebug>

GUI::GUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
    _timerId = startTimer(40); // Hz = 25

    // lat = 47.805;
    // lon = 12.997;
    // alt = 1408.3; // ft
}

GUI::~GUI()
{
    killTimer(_timerId);
    delete ui;
}

void GUI::timerEvent(QTimerEvent *event)
{
    QWidget::timerEvent(event);

    if ( _connected )
    {
        receive();
        send();
    }
}

void GUI::connect()
{
    if ( !_socket.bind("", _local_port) )
    {
        std::cerr << "Error: bind failed" << std::endl;
        return;
    }

    if ( !_socket.connect(_remote_ip, _remote_port) )
    {
        std::cerr << "Error: connect failed" << std::endl;
        return;
    }

    if ( !_socket.setNonBlocking(true) )
    {
        std::cerr << "Error: setNonBlocking failed" << std::endl;
        return;
    }

    _connected = true;
    ui->label_Status->setText("CONNECTED");
}

void GUI::receive()
{
    while ( _socket.hasPendingDatagrams() )
    {
        int size = _socket.recv((char*)(&_xplane_to_gui), sizeof(_xplane_to_gui));
        if ( size == sizeof(_xplane_to_gui) )
        {
            ui->label_data->setText( QString::number(_xplane_to_gui.tick) );
        }
    }
}

void GUI::send()
{
    _gui_to_xplane.tick = _xplane_to_gui.tick;
    _gui_to_xplane.lat = ui->spinBoxLat->value();
    _gui_to_xplane.lon = ui->spinBoxLon->value();
    _gui_to_xplane.alt = ui->spinBoxAlt->value();
    int size = _socket.sendto((char*)(&_gui_to_xplane), sizeof(_gui_to_xplane), _remote_ip, _remote_port);
    if ( size != sizeof(_gui_to_xplane) )
    {
        std::cerr << "Error: send failed" << std::endl;
    }
}

void GUI::on_pushButton_Connect_clicked()
{
    if ( !_connected )
    {
        _remote_ip = ui->lineEdit_address->text().toStdString();
        _remote_port = ui->spinBox_SendPort->value();
        _local_port = ui->spinBox_RecvPort->value();

        connect();
        // connectQt();
        // connectBoost();
    }
}

void GUI::on_pushButton_Disconnect_clicked()
{
    if ( _connected )
    {

        ui->pushButton_Connect->setEnabled(true);
        ui->pushButton_Disconnect->setEnabled(false);
        ui->label_Status->setText("DISCONNECTED");
        _connected = false;
    }
}

void GUI::on_spinBox_data_valueChanged(int arg1)
{
    // _data_out.var = arg1;
}
