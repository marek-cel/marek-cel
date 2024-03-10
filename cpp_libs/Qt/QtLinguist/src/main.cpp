#include "MainWindow.h"

#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>

////////////////////////////////////////////////////////////////////////////////

int main( int argc, char *argv[] )
{
    QLocale::setDefault( QLocale::system() );

    QApplication app( argc, argv );

    QString locale = QLocale::system().name();
    QString lang_code = locale.mid( 0, locale.indexOf('_') );

    QTranslator translator;
    QTranslator translatorQt;

    translator.load( QString( ":/project_" ) + lang_code );

    translatorQt.load( QLocale::system(),
                       QString::fromUtf8("qt"),
                       QString::fromUtf8("_"),
                       QLibraryInfo::location(QLibraryInfo::TranslationsPath) );

    app.installTranslator( &translator );
    app.installTranslator( &translatorQt );

    MainWindow win;

    win.show();

    return app.exec();
}
