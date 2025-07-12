#ifndef WIDGET_H
#define WIDGET_H

#include <memory>

#include <QWidget>

#include <QVTKOpenGLNativeWidget.h>
#include <vtkCameraOrientationWidget.h>

#include <SPH.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:

    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:

    void timerEvent(QTimerEvent *event) override;

private:

    Ui::Widget* _ui;

    int _timerId = 0;

    double _container_width  = 1.0;
    double _container_length = 2.0;
    double _container_depth  = 1.0;

    std::shared_ptr<SPH> _sph;

    vtkSmartPointer<vtkCameraOrientationWidget> _cameraOrientationWidget;

    void initVTK();
};

#endif // WIDGET_H
