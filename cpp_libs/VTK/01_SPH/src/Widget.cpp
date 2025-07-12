#include <Widget.h>
#include <ui_Widget.h>

#include <iostream>

#include <vtkActor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>


////////////////////////////////////////////////////////////////////////////////

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::Widget)
{
    _ui->setupUi(this);

    _sph = std::make_shared<SPH>(_container_length, _container_width, _container_depth);

    initVTK();

    _timerId = startTimer(1000 / 60); // 60 FPS_timerId = startTimer(1000 / 60); // 60 FPS
}

Widget::~Widget()
{
    delete _ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
    QWidget::timerEvent(event);
    double dt = 1.0 / 60.0; // Assuming 60 FPS
    _sph->update(dt);

}

void Widget::initVTK()
{
    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    _ui->openGLWidget->setRenderWindow(renderWindow);

    ///////////////////////////////////////////////////////

    // Create points.
    vtkNew<vtkPointSource> src;
    src->SetCenter(0, 0, 0);
    src->SetNumberOfPoints(_sph->getParticles().size());

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(src->GetOutputPort());

    vtkNew<vtkActor> pointsCloudActor;
    pointsCloudActor->SetMapper(mapper);
    pointsCloudActor->GetProperty()->SetColor(
        colors->GetColor4d("Tomato").GetData()
    );
    pointsCloudActor->GetProperty()->SetPointSize(5.0);

    ///////////////////////////////////////////////////////

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(pointsCloudActor);
    renderer->ResetCamera();
    colors->SetColor("BkgColor", std::array<unsigned char, 4>{26, 51, 102, 255}.data());
    renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());

    _ui->openGLWidget->renderWindow()->AddRenderer(renderer);

    _cameraOrientationWidget = vtkNew<vtkCameraOrientationWidget>();
    _cameraOrientationWidget->SetParentRenderer(renderer);
    _cameraOrientationWidget->CreateDefaultRepresentation();
    _cameraOrientationWidget->On();

}
