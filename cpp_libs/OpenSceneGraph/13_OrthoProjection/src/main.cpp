#include <iostream>

#include <osg/Geode>
#include <osg/ShapeDrawable>

#include <osgGA/StandardManipulator>
#include <osgGA/StateSetManipulator>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

class ManipulatorOrtho : public osgGA::StandardManipulator
{
public:

    ManipulatorOrtho()
        : osgGA::StandardManipulator()
    {}

    void setTransformation(const osg::Vec3d& eye, const osg::Quat& rotation)
    {
        // TODO
    }


    void setTransformation(const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up)
    {
        // TODO
    }


    void getTransformation(osg::Vec3d& eye, osg::Quat& rotation) const
    {
        // TODO
    }


    void getTransformation(osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up) const
    {
        // TODO
    }


    void setByMatrix(const osg::Matrixd& matrix)
    {
        // TODO
    }


    void setByInverseMatrix(const osg::Matrixd& matrix)
    {
        // TODO
    }

    osg::Matrixd getMatrix() const
    {
        // TODO
        return osg::Matrixd::identity();
    }


    osg::Matrixd getInverseMatrix() const
    {
        // TODO
        return osg::Matrixd::identity();
    }

    void updateCamera(osg::Camera& camera) override
    {
        osgGA::StandardManipulator::updateCamera(camera);

        double w2h = (double)(camera.getGraphicsContext()->getTraits()->width)
                / (double)(camera.getGraphicsContext()->getTraits()->height);

        double x_min = -_scale * _fov_y * w2h / 2.0;
        double x_max =  _scale * _fov_y * w2h / 2.0;
        double y_min = -_scale * _fov_y / 2.0;
        double y_max =  _scale * _fov_y / 2.0;

        if ( x_min != _x_min || x_max != _x_max || y_min != _y_min || y_max != _y_max )
        {
            _x_min = x_min;
            _x_max = x_max;
            _y_min = y_min;
            _y_max = y_max;

            camera.setProjectionMatrixAsOrtho(_x_min, _x_max, _y_min, _y_max, _z_near, _z_far);
        }
    }

    void setFovY(double fov_y)
    {
        if ( fov_y > 0.0 )
        {
            _fov_y = fov_y;
        }
    }

    void setScale(double scale)
    {
        _scale = scale;

        if ( _scale > _scale_max ) _scale = _scale_max;
        if ( _scale < _scale_min ) _scale = _scale_min;
    }


    void setScaleMin(double min)
    {
        if ( min >= 0.0 && min < _scale_max )
        {
            _scale_min = min;
        }
    }


    void setScaleMax(double max)
    {
        if ( max >= 0.0 && max > _scale_min )
        {
            _scale_max = max;
        }
    }

    void setWheelZoomFactor(double wheelZoomFactor)
    {
        _wheelZoomFactor = wheelZoomFactor;
    }

protected:

    double _fov_y = 1.0;

    double _x_min = -_fov_y / 2.0;
    double _x_max =  _fov_y / 2.0;
    double _y_min = -_fov_y / 2.0;
    double _y_max =  _fov_y / 2.0;

    double _scale = 1.0;
    double _scale_min = 0.1;
    double _scale_max = 100.0;

    double _z_near = 0.001;
    double _z_far = 1000.0;

    double _wheelZoomFactor = -0.1;

    bool handleMouseWheel(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us) override
    {
        osgGA::GUIEventAdapter::ScrollingMotion sm = ea.getScrollingMotion();

        switch ( sm )
        {
        case osgGA::GUIEventAdapter::SCROLL_UP:
            zoomModel( -_wheelZoomFactor );
            us.requestRedraw();
            return true;

        case osgGA::GUIEventAdapter::SCROLL_DOWN:
            zoomModel(  _wheelZoomFactor );
            us.requestRedraw();
            return true;
        }

        return false;
    }

    void zoomModel(const float dy)
    {
        std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
        setScale(_scale * (1.0 + dy));
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

    // set the custom manipulator
    osg::ref_ptr<ManipulatorOrtho> manipulator = new ManipulatorOrtho();
    viewer->setCameraManipulator(manipulator.get());
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

    constexpr double fov_y = 50.0;
    constexpr double fov_y_2 = fov_y / 2.0;

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
