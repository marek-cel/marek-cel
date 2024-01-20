#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>

#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>

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

    Phonon::AudioOutput *_audioOutput;
    Phonon::MediaObject *_mediaObject;
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
