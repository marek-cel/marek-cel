#ifndef WIDGETCGI_H
#define WIDGETCGI_H

#include <QDateTime>
#include <QGridLayout>
#include <QWidget>

#include <SceneRoot.h>

#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>

#include <GraphicsWindowQt.h>

class WidgetCGI : public QWidget, public osgViewer::Viewer
{
    Q_OBJECT

public:

    SceneRoot* _sceneRoot = nullptr;

    WidgetCGI(QWidget* parent = nullptr);
    virtual ~WidgetCGI();

    void update();

protected:

    void paintEvent( QPaintEvent *event );

private:

    QGridLayout* _gridLayout = nullptr;
    osg::ref_ptr< GraphicsWindowQt > _gwin;

    QWidget* addViewWidget();
    void createCamera();
    GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h,
                                            const std::string &name = "",
                                            bool windowDecoration = false );
};

#endif // WIDGETCGI_H
