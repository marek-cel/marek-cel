#ifndef WIDGETMAP_H
#define WIDGETMAP_H

////////////////////////////////////////////////////////////////////////////////

#include <QDateTime>
#include <QGridLayout>
#include <QWidget>

#include <map/Map.h>
#include <map/ManipulatorMap.h>

#include <osgViewer/Viewer>

#include <gui/GraphicsWindowQt.h>

////////////////////////////////////////////////////////////////////////////////

/** */
class WidgetMap : public QWidget, public osgViewer::Viewer
{
    Q_OBJECT

public:

    /** Constructor. */
    WidgetMap( QWidget *parent = 0 );

    /** Destructor. */
    virtual ~WidgetMap();

    /** */
    void update();

signals:

    void mouseMoveGeoPosition( const QString & );

protected:

    /** */
    void contextMenuEvent( QContextMenuEvent *event );

    /** */
    void paintEvent( QPaintEvent *event );

    /** */
    void timerEvent( QTimerEvent *event );

private:

    QGridLayout *_gridLayout;

    osg::ref_ptr< GraphicsWindowQt > _gwin;

    Map *_map;

    osg::ref_ptr<ManipulatorMap> _manipulator; ///< map camera manipulator

    QString _mouseGeoPositionStr;   ///<

    int _timerId;                   ///< timer ID

    double _lon_0;
    double _lat_0;

    bool _viewWoodland;             ///<
    bool _viewBuiltup;              ///<
    bool _viewInWaters;             ///<
    bool _viewRoads;                ///<

    QWidget* addViewWidget();

    void createCamera();

    GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h,
                                            const std::string &name = "",
                                            bool windowDecoration = false );

    void updateMouseGeoPositionStr( double lat, double lon );

private slots:

    void actionViewWoodland_toggled  ( bool checked );
    void actionViewBuiltup_toggled   ( bool checked );
    void actionViewInWaters_toggled  ( bool checked );
    void actionViewRoads_toggled     ( bool checked );

    void actionCenterView_triggered();
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETMAP_H
