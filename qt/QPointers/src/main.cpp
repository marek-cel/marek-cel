#include <iostream>

#include <QPointer>


#include "MyClass.h"

////////////////////////////////////////////////////////////////////////////////

void fun1()
{
    QPointer<MyClass> ptr( new MyClass("1") );
    ptr->doSomething();
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void fun2()
{
    QPointer<MyClass> ptr( new MyClass("2") );
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
}

////////////////////////////////////////////////////////////////////////////////

void fun3()
{
    QScopedPointer<MyClass> ptr( new MyClass("3") );
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
    ptr->doSomething();
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

    return 0;
}
