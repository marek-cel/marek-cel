#include "MainWindow.h"
#include "ui_MainWindow.h"

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow() ),

    _audioOutput ( nullptr ),
    _mediaObject ( nullptr )
{
    _ui->setupUi( this );

    _audioOutput = new Phonon::AudioOutput( Phonon::GameCategory, this );
    _mediaObject = new Phonon::MediaObject( this );

    //_mediaObject->setTickInterval( 1000 );

    Phonon::createPath( _mediaObject, _audioOutput );

    Phonon::MediaSource mediaSource( "../data/engine.ogg" );
    _mediaObject->setCurrentSource( mediaSource );
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( _audioOutput ) delete _audioOutput;
    _audioOutput = nullptr;

    if ( _mediaObject ) delete _mediaObject;
    _mediaObject = nullptr;

    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonPlay_clicked()
{
    if ( _mediaObject ) _mediaObject->play();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonStop_clicked()
{
    if ( _mediaObject ) _mediaObject->stop();
}
