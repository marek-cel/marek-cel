#include <iostream>

#include <QApplication>
#include <QDir>
#include <QMetaType>

#include <defs.h>
#include <MainWindow.h>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

//#   ifdef _LINUX_
//    setenv("LC_NUMERIC", "en_US", 1);
//#   endif // _LINUX_

    QApplication *app = new QApplication(argc, argv);

    app->setApplicationName    ( APP_NAME   );
    app->setApplicationVersion ( APP_VER    );
    app->setOrganizationDomain ( ORG_DOMAIN );
    app->setOrganizationName   ( ORG_NAME   );

    MainWindow *win = new MainWindow();
    win->show();
    int result = app->exec();

    delete win; win = nullptr;
    delete app; app = nullptr;

    return result;
}
