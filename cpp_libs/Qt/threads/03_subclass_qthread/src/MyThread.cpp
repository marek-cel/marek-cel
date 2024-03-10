#include "MyThread.h"

#include <QThread>
#include <QDebug>

MyThread::MyThread(QObject *parent)
    : QThread( parent )
{
    qDebug() << __func__ << " " << currentThread();
}

MyThread::~MyThread()
{
    qDebug() << __func__ << " " << currentThread();
}

void MyThread::doCount()
{
    const int count_max = 2e4;
    //const int count_max = 1e4;

    double percentage = 0.0;

    for ( int i = 0; i < count_max; ++i )
    {
        percentage = ( 100.0*i ) / ( count_max - 1 );

        qDebug() << "func " << percentage
                  << " " << currentThread()
                  << " " << currentThreadId();

        if ( i % ( count_max / 100 ) == 0 )
        {
            emit( currentCount(percentage) );
        }
    }

    emit( currentCount(percentage) );
    emit( countFinished() );
}

void MyThread::run()
{
    qDebug() << __func__ << " " << currentThread();

    doCount();

    // keeps thread running
    exec();
}
