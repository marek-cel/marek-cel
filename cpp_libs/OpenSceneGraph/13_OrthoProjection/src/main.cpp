#include <iostream>

#include <osg/Geode>
#include <osg/ShapeDrawable>

#include <osgGA/StateSetManipulator>
#include <osgGA/CameraManipulator>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

constexpr double fov_y = 50.0;
constexpr double fov_y_2 = fov_y / 2.0;

// Custom orthographic projection camera manipulator class
class OrthoCameraManipulator : public osgGA::CameraManipulator
{
public:
    OrthoCameraManipulator()
        : _center(0.0, 0.0, 0.0)
        , _distance(100.0)
        , _zoom(1.0)
        , _isPanning(false)
    {
    }

    virtual const char* className() const override { return "OrthoCameraManipulator"; }

    virtual void setByMatrix(const osg::Matrixd& matrix) override
    {
        _center = osg::Vec3d(0.0, 0.0, 0.0);
        _distance = matrix.getTrans().length();
    }

    virtual void setByInverseMatrix(const osg::Matrixd& matrix) override
    {
        setByMatrix(osg::Matrixd::inverse(matrix));
    }

    virtual osg::Matrixd getMatrix() const override
    {
        return osg::Matrixd::translate(0.0, 0.0, _distance) * osg::Matrixd::translate(_center);
    }

    virtual osg::Matrixd getInverseMatrix() const override
    {
        return osg::Matrixd::translate(-_center) * osg::Matrixd::translate(0.0, 0.0, -_distance);
    }

    virtual void home(double /*currentTime*/) override
    {
        _center.set(0.0, 0.0, 0.0);
        _distance = 100.0;
        _zoom = 1.0;
    }

    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override
    {
        switch(ea.getEventType())
        {
            case osgGA::GUIEventAdapter::PUSH:
            {
                if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON ||
                    ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
                {
                    _isPanning = true;
                    _lastMouseX = ea.getX();
                    _lastMouseY = ea.getY();
                    return true;
                }
                break;
            }

            case osgGA::GUIEventAdapter::RELEASE:
            {
                if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON ||
                    ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
                {
                    _isPanning = false;
                    return true;
                }
                break;
            }

            case osgGA::GUIEventAdapter::DRAG:
            {
                if (_isPanning)
                {
                    float dx = ea.getX() - _lastMouseX;
                    float dy = ea.getY() - _lastMouseY;

                    // Get the camera and viewport dimensions
                    osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
                    if (view)
                    {
                        osg::Camera* camera = view->getCamera();
                        const osg::Viewport* viewport = camera->getViewport();
                        
                        if (viewport)
                        {
                            double w2h = viewport->width() / viewport->height();
                            
                            // Scale pan movement to match orthographic projection scale
                            // Multiply by _zoom to account for current zoom level
                            double scaleX = (fov_y * w2h * _zoom) / viewport->width();
                            double scaleY = (fov_y * _zoom) / viewport->height();
                            
                            _center.x() -= dx * scaleX;
                            _center.y() -= dy * scaleY;
                        }
                    }

                    _lastMouseX = ea.getX();
                    _lastMouseY = ea.getY();
                    return true;
                }
                break;
            }

            case osgGA::GUIEventAdapter::SCROLL:
            {
                // Zoom in/out by adjusting the orthographic scale
                if (ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP)
                {
                    _zoom *= 0.9;
                    updateOrthoProjection(aa);
                }
                else if (ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_DOWN)
                {
                    _zoom *= 1.1;
                    updateOrthoProjection(aa);
                }
                return true;
            }

            default:
                break;
        }

        return false;
    }

private:
    osg::Vec3d _center;
    double _distance;
    double _zoom;
    bool _isPanning;
    float _lastMouseX;
    float _lastMouseY;

    void updateOrthoProjection(osgGA::GUIActionAdapter& aa)
    {
        osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
        if (view)
        {
            osg::Camera* camera = view->getCamera();
            const osg::Viewport* viewport = camera->getViewport();
            
            if (viewport)
            {
                double w2h = viewport->width() / viewport->height();
                double scaledFovY = fov_y_2 * _zoom;
                camera->setProjectionMatrixAsOrtho(
                    -scaledFovY * w2h, scaledFovY * w2h, 
                    -scaledFovY, scaledFovY, 
                    0.1, 1000000.0
                );
            }
        }
    }
};


void setupEventHandlers(osgViewer::Viewer* viewer)
{
    // add the state manipulator
    viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

    // add the thread model handler
    viewer->addEventHandler(new osgViewer::ThreadingHandler);

    // add the window size toggle handler
    viewer->addEventHandler(new osgViewer::WindowSizeHandler);

    // add the stats handler
    viewer->addEventHandler(new osgViewer::StatsHandler);

    // set the ortho projection camera manipulator
    viewer->setCameraManipulator(new OrthoCameraManipulator());
}

void setupCamera(osgViewer::Viewer* viewer)
{
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
    if ( camera.valid() == false )
    {
        std::cerr << "Error: Camera is invalid." << std::endl;
        return;
    }

    osg::GraphicsContext* context = camera->getGraphicsContext();
    if ( context == nullptr )
    {
        std::cerr << "Error: GraphicsContext is null." << std::endl;
        return;
    }

    const osg::GraphicsContext::Traits* traits = camera->getGraphicsContext()->getTraits();

    double w2h = static_cast<double>(traits->width)
               / static_cast<double>(traits->height);

    camera->setProjectionMatrixAsOrtho(-fov_y_2 * w2h, fov_y_2 * w2h, -fov_y_2, fov_y_2, 0.1, 1000000.0);
}

osg::Group* createScene()
{
    osg::ref_ptr<osg::Group> root = new osg::Group();

    osg::ref_ptr<osg::StateSet> stateSet = root->getOrCreateStateSet();
    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    root->addChild(geode.get());

    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3f(), 10.0, 10.0, 10.0);

    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(box.get());
    geode->addDrawable(shape.get());

    return root.release();
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    osgViewer::Viewer viewer;
    
    setupEventHandlers(&viewer);
    

    viewer.setUpViewInWindow(400, 200, 800, 600);
    viewer.setSceneData(createScene());

    setupCamera(&viewer);

    return viewer.run();
}