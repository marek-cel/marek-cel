#ifndef GUI_H
#define GUI_H

#include <memory>

#include <QWidget>

#include "XplaneToGUI.h"

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

    XplaneToGUI _xplane_to_gui;

    QString _remote_ip;
    int _remote_port;
    int _local_port;

    bool _connected = false;

private slots:

    void on_pushButton_Connect_clicked();
};

#endif // GUI_H
