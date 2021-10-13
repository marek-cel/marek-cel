#include <iostream>

#include <QPointer>

#include "MyClass.h"
#include "MyQObject.h"

////////////////////////////////////////////////////////////////////////////////

void fun1()
{
    QPointer<MyQObject> ptr( new MyQObject("1") );
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
    ptr->doSomething();
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void fun2()
{
    QPointer<MyQObject> ptr( new MyQObject("2") );
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
    ptr->doSomething();

    delete ptr;

    if ( ptr )
    {
        ptr->doSomething();
    }
    else
    {
        std::cout << __func__ << " ptr in NULL" << std::endl;
    }

    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void fun3()
{
    QScopedPointer<MyQObject> ptr( new MyQObject("3") );
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
    ptr->doSomething();
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void fun4()
{
    QSharedPointer<MyClass> ptr( new MyClass("4") );
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
    ptr->doSomething();
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

int main( int argc, char *argv[] )
{
    fun1();
    std::cout << std::endl;
    fun2();
    std::cout << std::endl;
    fun3();
    std::cout << std::endl;
    fun4();
    std::cout << std::endl;

    return 0;
}
