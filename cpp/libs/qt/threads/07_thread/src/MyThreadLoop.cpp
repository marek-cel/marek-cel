#include "MyThreadLoop.h"

#include <QThread>
#include <QDebug>

////////////////////////////////////////////////////////////////////////////////

MyThreadLoop::MyThreadLoop( QObject *parent)
    : QThread( parent )
{
    qDebug() << __func__ << " " << currentThread();

    _count = 0;
    _count_max = 1e9;
}

////////////////////////////////////////////////////////////////////////////////

MyThreadLoop::~MyThreadLoop()
{
    qDebug() << __func__ << " " << currentThread();
}

////////////////////////////////////////////////////////////////////////////////

void MyThreadLoop::doWork()
{
    double percentage = 0.0;

    for ( int i = 0; i < _count_max; i++ )
    {
        percentage = ( 100.0 * i ) / ( _count_max - 1 );

        if ( i % ( _count_max / 100 ) == 0 )
        {
            qDebug() << __func__ << " " << percentage << " " << QThread::currentThread();
            emit( currentCount(percentage) );
        }
    }

    emit( currentCount(percentage) );
    emit( countFinished() );
}

////////////////////////////////////////////////////////////////////////////////

void MyThreadLoop::run()
{
    qDebug() << __func__ << " " << currentThread();

    doWork();

    // doesnt need an event loop
    //exec(); // runs event loop
}
