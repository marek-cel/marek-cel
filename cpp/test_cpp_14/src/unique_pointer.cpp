#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class MyClass
{
public:

    MyClass()
    {
        cout << "MyClass()" << endl;
    }

    MyClass( int a, int b)
    {
        cout << "MyClass(int,int) " << a << " " << b << endl;
    }

    ~MyClass()
    {
        cout << "~MyClass()" << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////

void fun()
{
    std::unique_ptr< MyClass > my_class1 = std::make_unique< MyClass >( 1, 2 );

    throw( exception() );
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    try
    {
        fun();
    }
    catch ( ... )
    {
        cout << "Excpetion" << endl;
    }

    return 0;
}
