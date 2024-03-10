#ifndef MYTHREADTIMER_H
#define MYTHREADTIMER_H

////////////////////////////////////////////////////////////////////////////////

#include <QThread>
#include <QTimer>

////////////////////////////////////////////////////////////////////////////////

class MyThreadTimer : public QThread
{
    Q_OBJECT

public:

    explicit MyThreadTimer( int interval, QObject *parent = nullptr );

    ~MyThreadTimer() override;

signals:

    void currentCount(int);

    void countFinished();

public slots:

    void doWork();

protected:

    void run() override;

private:

    QTimer *_timer;

    int _count;
    int _count_max;

    int _interval;
};

////////////////////////////////////////////////////////////////////////////////

#endif // MYTHREADTIMER_H
