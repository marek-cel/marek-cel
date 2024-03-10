#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>

#include <AL/al.h>
#include <AL/alc.h>

#include <AL/alut.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class MainWindow;
}

////////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow( QWidget *parent = nullptr );

    ~MainWindow();

private slots:

    void on_pushButtonPlay_clicked();

    void on_pushButtonStop_clicked();

private:

    Ui::MainWindow *_ui;

    ALCdevice *_device;
    ALCcontext *_context;
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
