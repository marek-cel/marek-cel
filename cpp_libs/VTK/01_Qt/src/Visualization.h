#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <vector>

#include <vtkActor.h>
#include <vtkCameraOrientationWidget.h>
#include <vtkFloatArray.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkLookupTable.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>

#include <Particle.h>

class Visualization
{
public:

    Visualization();

    void init();
    void update(const std::vector<Particle>& particles);

    void setPointsVisibility(bool visible)
    {
        _actorPoints->SetVisibility(visible);
    }

    void setSurfaceVisibility(bool visible)
    {
        _actorSurface->SetVisibility(visible);
    }

    void setViewDefault();
    void setViewTop();
    void setViewBottom();
    void setViewLeft();
    void setViewRight();
    void setViewBack();
    void setViewFront();
    void setViewOrthographic();
    void setViewPerspective();
    void toggleViewOrthographic();

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> getRenderWindow() const { return _renderWindow; }
    vtkSmartPointer<vtkRenderer> getRenderer() const { return _renderer; }

protected:

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> _renderWindow;
    vtkSmartPointer<vtkRenderer> _renderer;

    vtkSmartPointer<vtkCameraOrientationWidget> _cameraOrientationWidget;

    vtkSmartPointer<vtkPolyData> _polyData;
    vtkSmartPointer<vtkPoints> _points;
    vtkSmartPointer<vtkCellArray> _vertices;
    vtkSmartPointer<vtkFloatArray> _densities;

    vtkSmartPointer<vtkLookupTable> _lutColorScale;

    vtkSmartPointer<vtkPolyDataMapper> _mapperPoints;
    vtkSmartPointer<vtkPolyDataMapper> _mapperContainer;
    vtkSmartPointer<vtkPolyDataMapper> _mapperSurface;

    vtkSmartPointer<vtkActor> _actorPoints;
    vtkSmartPointer<vtkActor> _actorContainer;
    vtkSmartPointer<vtkActor> _actorSurface;

    bool _viewOrtho = false;

    double _shift = 1.0;

    void initPoints();
    void initContainer();
    void initSurface();
};

#endif // VISUALIZATION_H
