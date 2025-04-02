#ifndef WIDGETCGI_H
#define WIDGETCGI_H

////////////////////////////////////////////////////////////////////////////////

#include <QDateTime>
#include <QGridLayout>
#include <QWidget>

#include <cgi/SceneRoot.h>

#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>

#include <gui/GraphicsWindowQt.h>

////////////////////////////////////////////////////////////////////////////////

/** This is widget wrapper for CGI. */
class WidgetCGI : public QWidget, public osgViewer::Viewer
{
    Q_OBJECT

public:

    /** Constructor. */
    WidgetCGI( QWidget *parent = 0 );

    /** Destructor. */
    virtual ~WidgetCGI();

    /** */
    void update();

protected:

    /** */
    void paintEvent( QPaintEvent *event );

private:

    QGridLayout *_gridLayout;

    osg::ref_ptr< GraphicsWindowQt > _gwin;

    SceneRoot *_sceneRoot;

    QWidget* addViewWidget();

    void createCamera();

    GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h,
                                            const std::string &name = "",
                                            bool windowDecoration = false );
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETCGI_H
