#include "worker.h"

#include <QDebug>
#include <QThread>

int Worker::count = 0;

Worker::Worker()
{

    ++count;
    qDebug() << __func__ << " " << count << " " << QThread::currentThread();
}

Worker::~Worker()
{
    --count;
    qDebug() << __func__ << " " << count << " " << QThread::currentThread();
}

void Worker::run()
{
    qDebug() << __func__ << " " << QThread::currentThread();

    //const int count_max = 2e4;
    const int count_max = 1e3;

    double percentage = 0.0;

    for ( int i = 0; i < count_max; ++i )
    {
        percentage = ( 100.0*i ) / ( count_max - 1 );

        if ( i % 1 == 0 )
        {
            qDebug() << "func " << percentage
                     << " " << QThread::currentThread()
                     << " " << QThread::currentThreadId();
        }
    }
}
