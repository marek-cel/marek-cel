#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>

class MyClass : public QObject
{
    Q_OBJECT

public:

    MyClass(const QString &name, QObject *parent = Q_NULLPTR);

    ~MyClass();

    void doSomething();

private:

    QString _name;
};

#endif // MYCLASS_H
