#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgGA/TerrainManipulator>
#include <osgViewer/ViewerEventHandlers>

#include <WidgetCGI.h>

WidgetCGI::WidgetCGI(QWidget* parent)
    : QWidget(parent)
    , _sceneRoot(new SceneRoot())
{
    osg::setNotifyLevel(osg::WARN);
//    osg::setNotifyLevel(osg::DEBUG_INFO);

    setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
    //setThreadingModel(osgViewer::ViewerBase::ThreadPerContext);

    _gwin = createGraphicsWindow(x(), y(), width(), height());

    QWidget* widget = addViewWidget();

    _gridLayout = new QGridLayout(this);
    _gridLayout->setContentsMargins(1, 1, 1, 1);
    _gridLayout->addWidget(widget, 0, 0);

    setLayout(_gridLayout);
}

WidgetCGI::~WidgetCGI()
{
    if ( _sceneRoot ) delete _sceneRoot;
    _sceneRoot = 0;
}

void WidgetCGI::update()
{
    //////////////////
    QWidget::update();
    //////////////////
}

void WidgetCGI::paintEvent(QPaintEvent* event)
{
    ///////////////////////////
    QWidget::paintEvent(event);
    ///////////////////////////

    frame();
}

QWidget* WidgetCGI::addViewWidget()
{
    createCamera();

    setSceneData(_sceneRoot->getNode());
    addEventHandler(new osgViewer::StatsHandler);
    setCameraManipulator(new osgGA::TrackballManipulator());
    //setCameraManipulator(new osgGA::TerrainManipulator());

    assignSceneDataToCameras();

    return _gwin->getGLWidget();
}

void WidgetCGI::createCamera()
{
    osg::ref_ptr<osg::Camera> camera = getCamera();

    camera->setGraphicsContext(_gwin);

    const osg::GraphicsContext::Traits *traits = _gwin->getTraits();

    //camera->setClearColor(osg::Vec4( 0.0, 0.0, 1.0, 1.0 ));
    camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    double w2h = static_cast<double>(traits->width)/static_cast<double>(traits->height);
    camera->setProjectionMatrixAsPerspective(30.0f, w2h, 1.0, 1000.0);
}

GraphicsWindowQt* WidgetCGI::createGraphicsWindow(int x, int y, int w, int h,
                                                  const std::string& name,
                                                  bool windowDecoration)
{
    osg::DisplaySettings *displaySettings = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits();

    traits->windowName       = name;
    traits->windowDecoration = windowDecoration;
    traits->x                = x;
    traits->y                = y;
    traits->width            = w;
    traits->height           = h;
    traits->doubleBuffer     = true;
    traits->alpha            = displaySettings->getMinimumNumAlphaBits();
    traits->stencil          = displaySettings->getMinimumNumStencilBits();
    traits->sampleBuffers    = displaySettings->getMultiSamples();
    traits->samples          = displaySettings->getNumMultiSamples();
    traits->vsync            = false;

    return new GraphicsWindowQt(traits.get());
}
