#include "MyClass.h"

#include <iostream>

MyClass::MyClass(const QString &name)
{
    _name = name;
    std::cout << "MyClass::MyClass() " + _name.toStdString() << std::endl;
}

MyClass::~MyClass()
{
    std::cout << "MyClass::~MyClass() " + _name.toStdString() << std::endl;
}

void MyClass::doSomething()
{
    std::cout << "MyClass::doSomething() " + _name.toStdString() << std::endl;
}
