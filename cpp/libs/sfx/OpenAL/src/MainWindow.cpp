#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow() )
{
    _ui->setupUi( this );

    // DEVICE OPENING
    // The very first thing to do is to open a handle to a device.
    // This is done like this:

    _device = alcOpenDevice( NULL );

    if ( !_device )
    {
        std::cout << "Cannot open device." << std::endl;
    }

    // CONTEXT CREATION AND INITIALIZATION
    // In order to render an audio scene, we need to create and initialize a
    // context for this. We do this by the following calls:

    _context = alcCreateContext( _device, NULL );

    if ( !alcMakeContextCurrent( _context ) )
    {
        std::cout << "Cannot create context." << std::endl;
    }

    // SOURCE GENERATION
    // In order to playback audio, we must create an audio source objet, this
    // source is actually the "origin" of the audio sound. And as such must be
    // defined in the audio scene. If you combine audio with graphics, most
    // likely quite a lot of your graphics objects will also include an audio
    // source object.
    // Note that you hold a reference (id) to a source object, you don’t
    // manipulate the source object directly.

    ALuint source;

    alGenSources((ALuint)1, &source);
    // check for errors

    alSourcef(source, AL_PITCH, 1);
    // check for errors
    alSourcef(source, AL_GAIN, 1);
    // check for errors
    alSource3f(source, AL_POSITION, 0, 0, 0);
    // check for errors
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    // check for errors
    alSourcei(source, AL_LOOPING, AL_FALSE);
    // check for errros

    // BUFFER GENERATION
    // The buffer object is the object actually holding the raw audio stream,
    // alone a buffer does not do much but occupying memory, so we will see
    // later on what to do with it. Just like sources, we hold a reference to
    // the buffer object.

    ALuint buffer;

    alGenBuffers((ALuint)1, &buffer);
    // check for errors

    // LOADING AN AUDIO STREAM TO A BUFFER
    // We mentionned earlier in this document that OpenAL manipulates raw audio
    // streams and does not care about the audio format, since it is not its
    // scope.
    // In order to simplify let’s take the example of a WAV file (*.wav). In
    // order to ease the parsing of the WAV format (not that it’s particularly
    // complex, but I am lazy), we can either use alut, or libaudio for
    // instance.
    // Here is the example with alut:

    ALsizei size, freq;
    ALenum format;
    ALvoid *data;
    ALboolean loop = AL_FALSE;

    ALbyte file[] = "../../../data/engine.wav";
    alutLoadWAVFile( file, &format, &data, &size, &freq, &loop );
    // check for errors

    // loading the raw audio stream into our buffer:

    alBufferData(buffer, format, data, size, freq);
    // check for errors

    // BINDING A SOURCE TO A BUFFER
    // In order to actually output something to the playback device, we need to
    // bind the source with its buffer. Obviously you can bind the same buffer
    // to several sources and mix different buffers to the same source. Binding
    // is done like this:

    alSourcei(source, AL_BUFFER, buffer);
    // check for errors

    // PLAYING THE SOURCE
    // We now have everything ready to start playing our source. Do you remember
    // that we mentionned the audio rendering to be asynchronous in the
    // beginning?
    // This means that a call to alSourcePlay(), will start playing the source,
    // and return immediately, we don’t wait until the source is fully played.
    // The reason for this is actually very simple, since it is an audio scene,
    // one can perfectly want to stack up different sounds playing a different
    // moments.
    // The underlying implementation of alSourcePlay() in OpenAL Soft actually
    // spawns a detached thread as soon as you issue alSourcePlay(), so guess
    // what happens in the following code snippet:

    alSourcePlay(source);

    // cleanup context
    //alDeleteSources(1, &source);
    //alDeleteBuffers(1, &buffer);
    //_device = alcGetContextsDevice(_context);
    //alcMakeContextCurrent(NULL);
    //alcDestroyContext(_context);
    //alcCloseDevice(_device);
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( _ui ) delete _ui;
    _ui = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonPlay_clicked()
{

}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonStop_clicked()
{

}
