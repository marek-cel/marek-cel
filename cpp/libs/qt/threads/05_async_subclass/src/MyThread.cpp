#include "MyThread.h"

#include <QThread>
#include <QDebug>
#include <QTimer>

MyThread::MyThread(QObject *parent)
    : QThread( parent )
{
    qDebug() << __func__ << " " << currentThread();
}

MyThread::~MyThread()
{
    qDebug() << __func__ << " " << currentThread();
}

void MyThread::doWork()
{
    QTimer *timer = new QTimer();

    connect(timer, &QTimer::timeout, []()
    {
        qDebug() << "Timeout. " << QThread::currentThread();
    });

    timer->setInterval(1000);
    timer->start();
}

void MyThread::run()
{
    qDebug() << __func__ << " " << currentThread();

    doWork();

    ////////////////////////////////////////////
    exec(); // keeps thread running (event loop)
    ////////////////////////////////////////////
}
