#include <iostream>

#include <QApplication>
#include <QDir>
#include <QMetaType>

#include <gui/MainWindow.h>

#include <defs.h>

////////////////////////////////////////////////////////////////////////////////

/** This is application main function. */
int main( int argc, char *argv[] )
{
    setlocale( LC_ALL, "" );

//#   ifdef _LINUX_
//    setenv( "LC_NUMERIC", "en_US", 1 );
//#   endif

    QApplication *app = new QApplication( argc, argv );

    MainWindow *win = new MainWindow();

    app->setApplicationName( TEST_APP_NAME   );
    app->setApplicationVersion( TEST_APP_VER    );
    app->setOrganizationDomain( TEST_ORG_DOMAIN );
    app->setOrganizationName( TEST_ORG_NAME   );

    win->show();

    int result = app->exec();

    delete win; win = 0;
    delete app; app = 0;

    return result;
}
