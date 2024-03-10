#include "MyClass.h"

#include <QThread>
#include <QDebug>

MyClass::MyClass(QObject *parent)
    : QObject( parent )
{
    qDebug() << __func__ << " " << QThread::currentThread();
}

MyClass::~MyClass()
{
    qDebug() << __func__ << " " << QThread::currentThread();
}

void MyClass::doCount()
{
    //const int count_max = 5e4;
    const int count_max = 1e4;

    double percentage = 0.0;

    for ( int i = 0; i < count_max; ++i )
    {
        percentage = ( 100.0*i ) / ( count_max - 1 );

        qDebug() << "func " << percentage
                  << " " << QThread::currentThread()
                  << " " << QThread::currentThreadId();

        if ( i % 100 == 0 )
        {
            emit( currentCount(percentage) );
        }
    }

    emit( currentCount(percentage) );
    emit(countFinished());
}
