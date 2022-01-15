#include "Worker.h"

#include <QTimer>
#include <QThread>
#include <QDebug>

Worker::Worker(QObject *parent)
    : QObject( parent )
{
    qDebug() << __func__ << " " << QThread::currentThread();
}

Worker::~Worker()
{
    qDebug() << __func__ << " " << QThread::currentThread();
}

void Worker::doWork()
{
    QTimer *timer = new QTimer();

    connect(timer,&QTimer::timeout,[]()
    {
        qDebug() << "Timeout. " << QThread::currentThread();
    });

    timer->start();
    timer->setInterval(1000);
}

