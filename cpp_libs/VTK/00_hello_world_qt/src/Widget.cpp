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

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkVertexGlyphFilter.h>


////////////////////////////////////////////////////////////////////////////////

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::Widget)
{
    _ui->setupUi(this);
    _model = std::make_shared<Model>(2.0, 1.0, 1.0);
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
    _model->update(dt);
    updateVTK();
    _ui->openGLWidget->renderWindow()->Render();
    // _ui->openGLWidget->update();
}

void Widget::initVTK()
{
    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    _ui->openGLWidget->setRenderWindow(renderWindow);

    ///////////////////////////////////////////////////////

    // Create points.
    // Create the polydata, mapper, and actor
    _polyData = vtkNew<vtkPolyData>();
    _mapper = vtkNew<vtkPolyDataMapper>();
    _actor = vtkNew<vtkActor>();

    // Set up the visualization pipeline
    _mapper->SetInputData(_polyData);
    _actor->SetMapper(_mapper);

    // Set point properties
    _actor->GetProperty()->SetColor(1.0, 0.0, 0.0); // Red color
    _actor->GetProperty()->SetPointSize(5.0f);
    _actor->GetProperty()->SetRenderPointsAsSpheres(true);

    updateVTK();

    ///////////////////////////////////////////////////////

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(_actor);
    renderer->ResetCamera();
    colors->SetColor("BkgColor", std::array<unsigned char, 4>{26, 51, 102, 255}.data());
    renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());

    _ui->openGLWidget->renderWindow()->AddRenderer(renderer);

    _cameraOrientationWidget = vtkNew<vtkCameraOrientationWidget>();
    _cameraOrientationWidget->SetParentRenderer(renderer);
    _cameraOrientationWidget->CreateDefaultRepresentation();
    _cameraOrientationWidget->On();
}

void Widget::updateVTK()
{
    std::vector<Coordinates> coordinates = _model->getCoordinates();

    // Create points
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    // Add particle coordinates to points
    for (const auto& c : coordinates)
    {
        points->InsertNextPoint(c.x, c.y, c.z);
    }

    // Create vertices for each point
    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();
    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i)
    {
        vertices->InsertNextCell(1, &i);
    }

    // Update the polydata
    _polyData->SetPoints(points);
    _polyData->SetVerts(vertices);

    // Alternative approach using vertex glyph filter (commented out)
    // This can be used for more advanced point rendering
    /*
    vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
        vtkSmartPointer<vtkVertexGlyphFilter>::New();
    vertexFilter->SetInputData(_polyData);
    vertexFilter->Update();
    _mapper->SetInputConnection(vertexFilter->GetOutputPort());
    */

    // Mark the polydata as modified
    _polyData->Modified();
}
