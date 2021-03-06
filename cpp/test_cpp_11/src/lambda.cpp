#include <iostream>
#include <functional>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void foobar( std::function< void() > fun )
{
    fun();
}

////////////////////////////////////////////////////////////////////////////////

class MyClass
{
public:

    void foo()
    {
        foobar( [this](){ bar(); } );
    }

private:

    void bar()
    {
        cout << "MyClass::bar()" << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::shared_ptr<MyClass> mc = std::make_shared<MyClass>();

    mc->foo();

    return 0;
}
