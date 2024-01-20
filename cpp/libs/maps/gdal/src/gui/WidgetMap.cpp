#include <gui/WidgetMap.h>

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>

#include <osgViewer/ViewerEventHandlers>

#include <map/Mercator.h>

////////////////////////////////////////////////////////////////////////////////

void scaleChangeCallback( double scale )
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////

WidgetMap::WidgetMap( QWidget *parent ) :
    QWidget ( parent ),

    _gridLayout ( 0 ),

    _map ( new Map() ),

    _timerId ( 0 ),

    _lon_0 ( osg::DegreesToRadians( -157.9868 ) ),
    _lat_0 ( osg::DegreesToRadians(   21.4730 ) ),

    _viewSatellite ( true  ),
    _viewWoodland  ( true  ),
    _viewBuiltup   ( true  ),
    _viewInWaters  ( true  ),
    _viewRoads     ( true  )
{
    osg::setNotifyLevel( osg::WARN );
//    osg::setNotifyLevel( osg::DEBUG_INFO );

    setThreadingModel( osgViewer::ViewerBase::SingleThreaded );
    //setThreadingModel( osgViewer::ViewerBase::ThreadPerContext );

    _gwin = createGraphicsWindow( x(), y(), width(), height() );

    setMouseTracking( true );

    _manipulator = new ManipulatorMap();
    _manipulator->registerScaleChangeCallback( &scaleChangeCallback );
    _manipulator->setScaleMin( 1.0e-5 );//m_manipulator->setScaleMin( 5.0e-5 );
    _manipulator->setScaleMax( 1.0 );
    _manipulator->setMapHeight( 2.0 * 1.0e7 );
    _manipulator->setMapMinX( -Mercator::_max_x );
    _manipulator->setMapMaxX(  Mercator::_max_x );
    _manipulator->setMapMinY( -Mercator::_max_y );
    _manipulator->setMapMaxY(  Mercator::_max_y );
    _manipulator->setAllowThrow( true );
    _manipulator->setCenterX( Mercator::x( _lon_0 ) );
    _manipulator->setCenterY( Mercator::y( _lat_0 ) );
    _manipulator->setScale( 3.0e-3 );

    _map->setVisibilitySatellite ( _viewSatellite );
    _map->setVisibilityWoodland  ( _viewWoodland  );
    _map->setVisibilityBuiltup   ( _viewBuiltup   );
    _map->setVisibilityInWaters  ( _viewInWaters  );
    _map->setVisibilityRoads     ( _viewRoads     );

    QWidget *widget = addViewWidget();

    _gridLayout = new QGridLayout( this );
    _gridLayout->setContentsMargins( 1, 1, 1, 1 );
    _gridLayout->addWidget( widget, 0, 0 );

    setLayout( _gridLayout );

    _timerId = startTimer( 20 );
}

////////////////////////////////////////////////////////////////////////////////

WidgetMap::~WidgetMap()
{
    if ( _timerId ) killTimer( _timerId );

    if ( _map ) { delete _map; } _map = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::update()
{
    //////////////////
    QWidget::update();
    //////////////////
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::contextMenuEvent( QContextMenuEvent *event )
{
    QMenu menuContext( this );

    QMenu menuLayers( this );

    menuContext.addMenu( &menuLayers );

    menuLayers.setTitle( "Layers" );

    QAction actionViewSatellite ( this );
    QAction actionViewWoodland  ( this );
    QAction actionViewBuiltup   ( this );
    QAction actionViewInWaters  ( this );
    QAction actionViewRoads     ( this );
    QAction actionCenterView    ( this );

    actionViewSatellite .setText( "Show/Hide Satellite" );
    actionViewWoodland  .setText( "Show/Hide Forests" );
    actionViewBuiltup   .setText( "Show/Hide Cities" );
    actionViewInWaters  .setText( "Show/Hide Inland Waters" );
    actionViewRoads     .setText( "Show/Hide Roads" );
    actionCenterView    .setText( "Center View" );

    actionViewSatellite .setCheckable( true );
    actionViewWoodland  .setCheckable( true );
    actionViewBuiltup   .setCheckable( true );
    actionViewInWaters  .setCheckable( true );
    actionViewRoads     .setCheckable( true );

    actionViewSatellite .setChecked( _viewSatellite );
    actionViewWoodland  .setChecked( _viewWoodland  );
    actionViewBuiltup   .setChecked( _viewBuiltup   );
    actionViewInWaters  .setChecked( _viewInWaters  );
    actionViewRoads     .setChecked( _viewRoads     );

    connect( &actionViewSatellite , SIGNAL( toggled(bool) ), this, SLOT( actionViewSatellite_toggled (bool) ) );
    connect( &actionViewWoodland  , SIGNAL( toggled(bool) ), this, SLOT( actionViewWoodland_toggled  (bool) ) );
    connect( &actionViewBuiltup   , SIGNAL( toggled(bool) ), this, SLOT( actionViewBuiltup_toggled   (bool) ) );
    connect( &actionViewInWaters  , SIGNAL( toggled(bool) ), this, SLOT( actionViewInWaters_toggled  (bool) ) );
    connect( &actionViewRoads     , SIGNAL( toggled(bool) ), this, SLOT( actionViewRoads_toggled     (bool) ) );

    connect( &actionCenterView, SIGNAL( triggered() ), this, SLOT( actionCenterView_triggered() ) );

    menuLayers.addAction( &actionViewSatellite );
    menuLayers.addAction( &actionViewWoodland  );
    menuLayers.addAction( &actionViewBuiltup   );
    menuLayers.addAction( &actionViewInWaters  );
    menuLayers.addAction( &actionViewRoads     );

    menuContext.addAction( &actionCenterView );

    menuContext.exec( event->globalPos() );

    actionViewSatellite .disconnect();
    actionViewWoodland  .disconnect();
    actionViewBuiltup   .disconnect();
    actionViewInWaters  .disconnect();
    actionViewRoads     .disconnect();
    actionCenterView    .disconnect();
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::paintEvent( QPaintEvent *event )
{
    /////////////////////////////
    QWidget::paintEvent( event );
    /////////////////////////////

    frame();
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::timerEvent( QTimerEvent *event )
{
    /////////////////////////////
    QWidget::timerEvent( event );
    /////////////////////////////

    update();

    //_map->update();

    updateMouseGeoPositionStr( _manipulator->getMouseLat(),
                               _manipulator->getMouseLon() );

    emit mouseMoveGeoPosition( _mouseGeoPositionStr );
}

////////////////////////////////////////////////////////////////////////////////

QWidget* WidgetMap::addViewWidget()
{
    createCamera();

    setSceneData( _map->getNode() );
    addEventHandler( new osgViewer::StatsHandler );
    setCameraManipulator( _manipulator.get() );

    assignSceneDataToCameras();

    return _gwin->getGLWidget();
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::createCamera()
{
    osg::ref_ptr<osg::Camera> camera = getCamera();

    camera->setGraphicsContext( _gwin );

    const osg::GraphicsContext::Traits *traits = _gwin->getTraits();

    //camera->setClearColor( osg::Vec4( 0.0, 0.0, 1.0, 1.0 ) );
    camera->setViewport( new osg::Viewport( 0, 0, traits->width, traits->height ) );
    camera->setProjectionMatrixAsPerspective( 30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0, 1000.0 );
}

////////////////////////////////////////////////////////////////////////////////

GraphicsWindowQt* WidgetMap::createGraphicsWindow( int x, int y, int w, int h,
                                                   const std::string &name,
                                                   bool windowDecoration )
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

    return new GraphicsWindowQt( traits.get() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::updateMouseGeoPositionStr( double lat, double lon )
{
    double lat_deg = osg::RadiansToDegrees( fabs( lat ) );
    double lon_deg = osg::RadiansToDegrees( fabs( lon ) );

    int lat_d = floor( lat_deg );
    int lat_m = floor( 60.0 * ( lat_deg - lat_d ) );
    double lat_s = 3600.0 * ( lat_deg - lat_d - lat_m / 60.0 );

    int lon_d = floor( lon_deg );
    int lon_m = floor( 60.0 * ( lon_deg - lon_d ) );
    double lon_s = 3600.0 * ( lon_deg - lon_d - lon_m / 60.0 );

    _mouseGeoPositionStr.clear();

    _mouseGeoPositionStr += QString("%1").arg( lon_d, 3, 'f', 0, QChar(' ') );
    _mouseGeoPositionStr += QString::fromUtf8( "° " );
    _mouseGeoPositionStr += QString("%1").arg( lon_m, 2, 'f', 0, QChar('0') );
    _mouseGeoPositionStr += "' ";
    _mouseGeoPositionStr += QString("%1").arg( lon_s, 5, 'f', 2, QChar('0') );
    _mouseGeoPositionStr += "\"";
    _mouseGeoPositionStr += ( lon > 0.0 ) ? "E" : "W";

    _mouseGeoPositionStr += ",  ";

    _mouseGeoPositionStr += QString("%1").arg( lat_d, 2, 'f', 0, QChar(' ') );
    _mouseGeoPositionStr += QString::fromUtf8( "° " );
    _mouseGeoPositionStr += QString("%1").arg( lat_m, 2, 'f', 0, QChar('0') );
    _mouseGeoPositionStr += "' ";
    _mouseGeoPositionStr += QString("%1").arg( lat_s, 5, 'f', 2, QChar('0') );
    _mouseGeoPositionStr += "\"";
    _mouseGeoPositionStr += ( lat > 0.0 ) ? "N" : "S";
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::actionViewSatellite_toggled( bool checked )
{
    _viewSatellite = checked;
    _map->setVisibilitySatellite( checked );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::actionViewWoodland_toggled( bool checked )
{
    _viewWoodland = checked;
    _map->setVisibilityWoodland( checked );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::actionViewBuiltup_toggled( bool checked )
{
    _viewBuiltup = checked;
    _map->setVisibilityBuiltup( checked );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::actionViewInWaters_toggled( bool checked )
{
    _viewInWaters = checked;
    _map->setVisibilityInWaters( _viewInWaters );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::actionViewRoads_toggled( bool checked )
{
    _viewRoads = checked;
    _map->setVisibilityRoads( checked );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::actionCenterView_triggered()
{
    _manipulator->setCenterX( Mercator::x( _lon_0 ) );
    _manipulator->setCenterY( Mercator::y( _lat_0 ) );
}
