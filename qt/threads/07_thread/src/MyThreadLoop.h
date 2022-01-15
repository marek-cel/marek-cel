#ifndef MYTHREADLOOP_H
#define MYTHREADLOOP_H

////////////////////////////////////////////////////////////////////////////////

#include <QThread>
#include <QTimer>

////////////////////////////////////////////////////////////////////////////////

class MyThreadLoop : public QThread
{
    Q_OBJECT

public:

    explicit MyThreadLoop( QObject *parent = nullptr );

    ~MyThreadLoop() override;

signals:

    void currentCount(int);

    void countFinished();

public slots:

    void doWork();

protected:

    void run() override;

private:

    int _count;
    int _count_max;
};

////////////////////////////////////////////////////////////////////////////////

#endif // MYTHREADLOOP_H
