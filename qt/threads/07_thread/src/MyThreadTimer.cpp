#include "MyThreadTimer.h"

#include <QThread>
#include <QDebug>

////////////////////////////////////////////////////////////////////////////////

MyThreadTimer::MyThreadTimer( int interval, QObject *parent)
    : QThread( parent )
{
    qDebug() << __func__ << " " << currentThread();

    _count = 0;
    _count_max = 100;
    _interval = interval;
}

////////////////////////////////////////////////////////////////////////////////

MyThreadTimer::~MyThreadTimer()
{
    qDebug() << __func__ << " " << currentThread();
}

////////////////////////////////////////////////////////////////////////////////

void MyThreadTimer::doWork()
{
    _timer = new QTimer( this );

    connect( _timer, &QTimer::timeout, [&]()
    {
        if ( _count < _count_max )
        {
            _count++;
            double percentage = ( 100.0 * _count ) / _count_max;

            qDebug() << __func__ << " " << percentage << " " << QThread::currentThread();

            if ( _count % ( _count_max / 100 ) == 0 )
            {
                emit( currentCount(percentage) );
            }
        }
        else
        {
            emit( countFinished() );
        }
    });

    _timer->setInterval( _interval );
    _timer->start();
}

////////////////////////////////////////////////////////////////////////////////

void MyThreadTimer::run()
{
    qDebug() << __func__ << " " << currentThread();

    doWork();

    exec(); // runs event loop
}
