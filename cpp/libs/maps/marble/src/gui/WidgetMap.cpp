#include <gui/WidgetMap.h>

#include <marble/MarbleDirs.h>
#include <marble/MarbleGlobal.h>
#include <marble/MarbleLocale.h>
#include <marble/MarbleWidgetPopupMenu.h>

////////////////////////////////////////////////////////////////////////////////

WidgetMap::WidgetMap( QWidget *parent ) :
    Marble::MarbleWidget ( parent )
{
    QString dataPath = QDir::currentPath();
    dataPath += "/data/";
    Marble::MarbleDirs::setMarbleDataPath( dataPath );

    setMapThemeId( "earth/mymap/mymap.dgml" );
    //setMapThemeId( "earth/openstreetmap/openstreetmap.dgml" );
    //setMapThemeId( "earth/bluemarble/bluemarble.dgml" );

    //setProjection( Marble::Mercator );

    //inputHandler()->setInertialEarthRotationEnabled( false );

    Marble::MarbleGlobal::getInstance()->locale()->setMeasurementSystem( Marble::MarbleLocale::NauticalSystem );
}

////////////////////////////////////////////////////////////////////////////////

WidgetMap::~WidgetMap() {}

////////////////////////////////////////////////////////////////////////////////

bool WidgetMap::event( QEvent *event )
{
    // first!
    //setHeading( 0.0 );

    ////////////////////////////////////////////
    return Marble::MarbleWidget::event( event );
    ////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////

void WidgetMap::initMenu()
{
    popupMenu();
}
