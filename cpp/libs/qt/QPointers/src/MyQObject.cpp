#include "MyQObject.h"

#include <iostream>

MyQObject::MyQObject(const QString &name, QObject *parent) :
    QObject(parent)
{
    _name = name;
    std::cout << "MyQObject::MyQObject() " + _name.toStdString() << std::endl;
}

MyQObject::~MyQObject()
{
    std::cout << "MyQObject::~MyQObject() " + _name.toStdString() << std::endl;
}

void MyQObject::doSomething()
{
    std::cout << "MyQObject::doSomething() " + _name.toStdString() << std::endl;
}
