#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

class MyClass
{
public:

    MyClass()
    {
        std::cout << "MyClass::CONSTRUCTOR" << std::endl;
    }

    virtual ~MyClass()
    {
        std::cout << "MyClass::DESTRUCTOR" << std::endl;
    }

    void doSomething()
    {
        std::cout << "MyClass::doSomething()" << std::endl;
    }
};

////////////////////////////////////////////////////////////////////////////////

void fun1( std::weak_ptr<MyClass> wp )
{
    if ( !wp.expired() )
    {
        std::shared_ptr<MyClass> sp = wp.lock();
        sp->doSomething();
    }
}

////////////////////////////////////////////////////////////////////////////////

void fun2( std::weak_ptr<MyClass> wp )
{
    if ( !wp.expired() )
    {
        wp.lock()->doSomething();
    }
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::shared_ptr<MyClass> mc = std::make_shared<MyClass>();

    fun1( mc );
    fun2( mc );

    return 0;
}
