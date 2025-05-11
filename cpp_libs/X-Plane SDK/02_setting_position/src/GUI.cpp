#include "GUI.h"
#include "ui_GUI.h"

#include <QDebug>

GUI::GUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
    _timerId = startTimer(40); // Hz = 25


}

GUI::~GUI()
{
    killTimer(_timerId);
    delete ui;
}

void GUI::timerEvent(QTimerEvent *event)
{
    QWidget::timerEvent(event);
}

void GUI::on_pushButton_Connect_clicked()
{
    if ( !_connected )
    {
        _connected = true;

        ui->pushButton_Connect->setText("Disconnect");
    }
    else
    {
        _connected = false;

        ui->pushButton_Connect->setText("Connect");
    }
}
