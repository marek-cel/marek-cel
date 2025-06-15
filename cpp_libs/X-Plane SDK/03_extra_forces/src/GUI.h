#ifndef GUI_H
#define GUI_H

#include <memory>

#include <boost/asio.hpp>

#include <QWidget>

#include <databuf.h>
#include <UdpSocket.h>

namespace Ui {
class GUI;
}

class GUI : public QWidget
{
    Q_OBJECT

public:

    explicit GUI(QWidget *parent = nullptr);
    ~GUI();

protected:

    void timerEvent(QTimerEvent *event) override;

private:

    Ui::GUI *ui;

    int _timerId;

    std::string _remote_ip;
    uint16_t _remote_port;
    uint16_t _local_port;

    bool _connected = false;

    UdpSocket _socket;

    XPLANE_TO_GUI _xplane_to_gui;
    GUI_TO_XPLANE _gui_to_xplane;

    void connect();
    void receive();
    void send();

private slots:

    void on_pushButton_Connect_clicked();
    void on_pushButton_Disconnect_clicked();

    void on_spinBox_data_valueChanged(int arg1);
};

#endif // GUI_H
