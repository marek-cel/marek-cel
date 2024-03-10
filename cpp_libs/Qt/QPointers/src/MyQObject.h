#ifndef MYQOBJECT_H
#define MYQOBJECT_H

#include <QObject>

class MyQObject : public QObject
{
    Q_OBJECT

public:

    MyQObject(const QString &name, QObject *parent = Q_NULLPTR);

    ~MyQObject();

    void doSomething();

private:

    QString _name;
};

#endif // MYQOBJECT_H
