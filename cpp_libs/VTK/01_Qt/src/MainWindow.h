#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QElapsedTimer>
#include <QMainWindow>
#include <QShortcut>

#include <vtkActor.h>
#include <vtkCameraOrientationWidget.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>

#include <Simulation.h>
#include <Visualization.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    void timerEvent(QTimerEvent *event) override;

private:

    Ui::MainWindow* _ui;

    std::shared_ptr<QShortcut> _scViewDefault;
    std::shared_ptr<QShortcut> _scViewTop;
    std::shared_ptr<QShortcut> _scViewBottom;
    std::shared_ptr<QShortcut> _scViewLeft;
    std::shared_ptr<QShortcut> _scViewRight;
    std::shared_ptr<QShortcut> _scViewBack;
    std::shared_ptr<QShortcut> _scViewFront;
    std::shared_ptr<QShortcut> _scViewOrtho;

    QElapsedTimer _timer;

    int _timerId = 0;

    std::shared_ptr<Simulation> _sim;
    std::shared_ptr<Visualization> _vis;

    double _average_time_step = 0.0;

    void settingsRead();
    void settingsSave();

private slots:

    void on_actionViewDefault_triggered();
    void on_actionViewTop_triggered();
    void on_actionViewBottom_triggered();
    void on_actionViewLeft_triggered();
    void on_actionViewRight_triggered();
    void on_actionViewBack_triggered();
    void on_actionViewFront_triggered();
    void on_actionViewOrtho_triggered();
    void on_actionViewPoints_toggled(bool arg1);
    void on_actionViewSurface_toggled(bool arg1);
};

#endif // MAINWINDOW_H
