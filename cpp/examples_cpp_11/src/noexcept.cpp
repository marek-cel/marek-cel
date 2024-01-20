#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class MyClass
{
public:

    MyClass();

    ~MyClass() noexcept;

    void fun();
    void fun2() noexcept;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    try
    {
        MyClass *mc = new MyClass();
        mc->fun();
        delete mc;
    }
    catch ( const std::exception &ex )
    {
        cout << ">>> Exception: " << ex.what() << endl;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

MyClass::MyClass()
{
    cout << "MyClass()" << endl;
}

MyClass::~MyClass() noexcept
{
    cout << "~MyClass()" << endl;
    //throw std::exception();
}

void MyClass::fun()
{
    cout << "fun()" << endl;
}

//void MyClass::fun2() // ERROR: declaration of ‘void MyClass::fun2()’ has a different exception specifier
void MyClass::fun2() noexcept
{
    cout << "fun2()" << endl;
    //throw std::exception();
}
