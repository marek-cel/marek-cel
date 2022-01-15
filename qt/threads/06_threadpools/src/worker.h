#ifndef WORKER_H
#define WORKER_H

#include <QRunnable>

class Worker : public QRunnable
{
public:
    static int count;

    Worker();

    ~Worker() override;

    // QRunnable interface
public:
    void run() override;
};

#endif // WORKER_H
