#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

class MyClass
{
public:

    MyClass() {}

    void doSomething()
    {
        std::cout << "MyClass::doSomething()" << std::endl;
    }
};

////////////////////////////////////////////////////////////////////////////////

void fun( std::weak_ptr<MyClass> wp )
{
    if ( !wp.expired() )
    {
        std::shared_ptr<MyClass> sp = wp.lock();
        sp->doSomething();
    }
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::shared_ptr<MyClass> mc = std::make_shared<MyClass>();

    fun( mc );

    return 0;
}
