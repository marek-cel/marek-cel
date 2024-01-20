#ifndef WIDGETMAP_H
#define WIDGETMAP_H

////////////////////////////////////////////////////////////////////////////////

#include <marble/MarbleWidget.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Map widget class.
 */
class WidgetMap : public Marble::MarbleWidget
{
    Q_OBJECT

public:

    /** Constructor. */
    WidgetMap( QWidget *parent = 0 );

    /** Destructor. */
    virtual ~WidgetMap();

protected:

    bool event( QEvent *event );

private:

    void initMenu();
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETMAP_H
