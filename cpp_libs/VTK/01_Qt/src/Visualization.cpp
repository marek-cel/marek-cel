#include <Visualization.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCubeSource.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>

#include <vtkGaussianSplatter.h>
#include <vtkContourFilter.h>

#include <Container.h>

Visualization::Visualization()
{
    _shift = std::max({Container::length, Container::width, Container::height}) * 1.5;

    vtkNew<vtkNamedColors> colors;

    _renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    _polyData = vtkSmartPointer<vtkPolyData>::New();
    _points = vtkSmartPointer<vtkPoints>::New();
    _vertices = vtkSmartPointer<vtkCellArray>::New();
    _densities = vtkSmartPointer<vtkFloatArray>::New();

    // _lutColorScale = vtkSmartPointer<vtkLookupTable>::New();
    // _lutColorScale->SetNumberOfColors(256);
    // _lutColorScale->SetRange(0.0, 1000.0); // Set range for density values
    // _lutColorScale->SetHueRange(0.667, 0.0);
    // _lutColorScale->SetSaturationRange(1.0, 1.0);
    // _lutColorScale->SetValueRange(1.0, 1.0);
    // _lutColorScale->Build();

    initPoints();
    initContainer();
    initSurface();

    _renderer = vtkSmartPointer<vtkRenderer>::New();

    _renderer->AddActor(_actorPoints);
    _renderer->AddActor(_actorContainer);
    _renderer->AddActor(_actorSurface);

    _renderer->ResetCamera();

    // colors->SetColor("BkgColor", std::array<unsigned char, 4>{26, 51, 102, 255}.data());
    colors->SetColor("BkgColor", std::array<unsigned char, 4>{255, 255, 255, 255}.data());
    // _renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
    // _renderer->SetBackground(colors->GetColor3d("Gainsboro").GetData());
    // _renderer->SetBackground(colors->GetColor3d("Silver").GetData());
    _renderer->SetBackground(colors->GetColor3d("LightSteelBlue").GetData());
    // _renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
}

void Visualization::init()
{
    _cameraOrientationWidget = vtkSmartPointer<vtkCameraOrientationWidget>::New();
    _cameraOrientationWidget->SetParentRenderer(_renderer);
    _cameraOrientationWidget->CreateDefaultRepresentation();
    _cameraOrientationWidget->On();

    setViewOrthographic();
    setViewDefault();
    //setViewTop();
}

void Visualization::update(const std::vector<Particle>& particles)
{
    _points->Reset();
    for (const auto& p : particles)
    {
        _points->InsertNextPoint(p.x, p.y, p.z);
        // _densities->InsertNextValue(p.density);
    }

    _vertices->Reset();
    for (vtkIdType i = 0; i < _points->GetNumberOfPoints(); ++i)
    {
        _vertices->InsertNextCell(1, &i);
    }

    // Update the polydata
    _polyData->SetPoints(_points);
    _polyData->SetVerts(_vertices);
    // _polyData->GetPointData()->SetScalars(_densities);

    _points->Modified();
    _vertices->Modified();
    _polyData->Modified();
}

void Visualization::setViewDefault()
{
    double x = Container::length / 2.0;
    double y = Container::width  / 2.0;
    double z = Container::height / 2.0;

    vtkCamera* camera = _renderer->GetActiveCamera();
    camera->SetFocalPoint(x, y, z);
    camera->SetPosition(x + _shift, y + _shift, z + _shift);
    camera->SetViewUp(0, 0, 1);
    _renderer->ResetCameraClippingRange();
}

void Visualization::setViewTop()
{
    setViewOrthographic();
    vtkCamera* camera = _renderer->GetActiveCamera();
    double focalPoint[3];
    camera->GetFocalPoint(focalPoint);
    camera->SetPosition(focalPoint[0], focalPoint[1], focalPoint[2] + _shift);
    camera->SetViewUp(0, 1, 0);
    _renderer->ResetCameraClippingRange();
}

void Visualization::setViewBottom()
{
    setViewOrthographic();
    vtkCamera* camera = _renderer->GetActiveCamera();
    double focalPoint[3];
    camera->GetFocalPoint(focalPoint);
    camera->SetPosition(focalPoint[0], focalPoint[1], focalPoint[2] - _shift);
    camera->SetViewUp(0, -1, 0);
    _renderer->ResetCameraClippingRange();
}

void Visualization::setViewLeft()
{
    setViewOrthographic();
    vtkCamera* camera = _renderer->GetActiveCamera();
    double focalPoint[3];
    camera->GetFocalPoint(focalPoint);
    camera->SetPosition(focalPoint[0] - _shift, focalPoint[1], focalPoint[2]);
    camera->SetViewUp(0, 0, 1);
    _renderer->ResetCameraClippingRange();
}

void Visualization::setViewRight()
{
    setViewOrthographic();
    vtkCamera* camera = _renderer->GetActiveCamera();
    double focalPoint[3];
    camera->GetFocalPoint(focalPoint);
    camera->SetPosition(focalPoint[0] + _shift, focalPoint[1], focalPoint[2]);
    camera->SetViewUp(0, 0, 1);
    _renderer->ResetCameraClippingRange();
}

void Visualization::setViewBack()
{
    setViewOrthographic();
    vtkCamera* camera = _renderer->GetActiveCamera();
    double focalPoint[3];
    camera->GetFocalPoint(focalPoint);
    camera->SetPosition(focalPoint[0], focalPoint[1] - _shift, focalPoint[2]);
    camera->SetViewUp(0, 0, 1);
    _renderer->ResetCameraClippingRange();
}

void Visualization::setViewFront()
{
    setViewOrthographic();
    vtkCamera* camera = _renderer->GetActiveCamera();
    double focalPoint[3];
    camera->GetFocalPoint(focalPoint);
    camera->SetPosition(focalPoint[0], focalPoint[1] + _shift, focalPoint[2]);
    camera->SetViewUp(0, 0, 1);
    _renderer->ResetCameraClippingRange();
}

void Visualization::setViewOrthographic()
{
    _renderer->GetActiveCamera()->SetParallelProjection(true);
    _renderer->ResetCamera();
    _viewOrtho = true;
}

void Visualization::setViewPerspective()
{
    _renderer->GetActiveCamera()->SetParallelProjection(false);
    _renderer->ResetCamera();
    _viewOrtho = false;
}

void Visualization::toggleViewOrthographic()
{
    if (_viewOrtho)
    {
        setViewPerspective();
    }
    else
    {
        setViewOrthographic();
    }
}

void Visualization::initPoints()
{
    _mapperPoints = vtkSmartPointer<vtkPolyDataMapper>::New();
    _actorPoints = vtkSmartPointer<vtkActor>::New();

    _mapperPoints->SetInputData(_polyData);
    // _mapperPoints->SetLookupTable(_lutColorScale);
    // _mapperPoints->SetScalarRange(_densities->GetRange());

    _actorPoints->SetMapper(_mapperPoints);

    _actorPoints->GetProperty()->SetColor(0.0, 0.0, 1.0);
    _actorPoints->GetProperty()->SetPointSize(10.0f);
    _actorPoints->GetProperty()->SetRenderPointsAsSpheres(true);
}

void Visualization::initContainer()
{
    double x = Container::length / 2.0;
    double y = Container::width  / 2.0;
    double z = Container::height / 2.0;

    vtkNew<vtkCubeSource> cubeSource;
    cubeSource->SetXLength(Container::length);
    cubeSource->SetYLength(Container::width);
    cubeSource->SetZLength(Container::height);
    cubeSource->SetCenter(x, y, z);
    cubeSource->Update();

    _mapperContainer = vtkSmartPointer<vtkPolyDataMapper>::New();
    _mapperContainer->SetInputConnection(cubeSource->GetOutputPort());

    _actorContainer = vtkSmartPointer<vtkActor>::New();
    _actorContainer->SetMapper(_mapperContainer);
    _actorContainer->GetProperty()->SetRepresentationToWireframe();
    _actorContainer->GetProperty()->SetColor(0.5, 0.5, 0.5); // Gray color
}

void Visualization::initSurface()
{
    vtkSmartPointer<vtkGaussianSplatter> splatter = vtkSmartPointer<vtkGaussianSplatter>::New();
    splatter->SetInputData(_polyData);
    splatter->SetSampleDimensions(50, 50, 50); // Tune for resolution
    splatter->SetRadius(0.05);                  // Influence radius
    splatter->SetExponentFactor(-1.0);         // Controls falloff
    splatter->ScalarWarpingOff();              // Use density, not coordinates

    vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
    contour->SetInputConnection(splatter->GetOutputPort());
    contour->SetValue(0, 0.01); // Tune this isovalue

    _mapperSurface = vtkSmartPointer<vtkPolyDataMapper>::New();
    _mapperSurface->SetInputConnection(contour->GetOutputPort());
    _mapperSurface->ScalarVisibilityOff();

    _actorSurface = vtkSmartPointer<vtkActor>::New();
    _actorSurface->SetMapper(_mapperSurface);
    _actorSurface->GetProperty()->SetColor(0.1, 0.5, 1.0); // Fluid color
    _actorSurface->GetProperty()->SetOpacity(0.5); // Semi-transparent
    _actorSurface->SetVisibility(false); // Initially hidden
}

