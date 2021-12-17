#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>

class MyClass : public QObject
{
    Q_OBJECT

public:

    explicit MyClass( QObject *parent = nullptr );

    ~MyClass();

public slots:

    void doCount();

signals:

    void currentCount(int);

    void countFinished();
};

#endif // MYCLASS_H
