#ifndef WIDGET_H
#define WIDGET_H

#include <memory>

#include <QWidget>

#include <QVTKOpenGLNativeWidget.h>
#include <vtkActor.h>
#include <vtkCameraOrientationWidget.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>

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

    vtkSmartPointer<vtkPolyData> _polyData;
    vtkSmartPointer<vtkPolyDataMapper> _mapper;
    vtkSmartPointer<vtkActor> _actor;

    void initVTK();
    void updateVTK();
};

#endif // WIDGET_H
