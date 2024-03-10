#ifndef MYCLASS_H
#define MYCLASS_H

#include <QString>

class MyClass
{
public:

    MyClass(const QString &name);

    ~MyClass();

    void doSomething();

private:

    QString _name;
};

#endif // MYCLASS_H
