#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class BaseClass
{
public:

    BaseClass() {}

    virtual ~BaseClass() {}

    virtual void fun( int a, int b = 666 )
    {
        cout << a << " " << b << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////

class DerivedClass : public BaseClass
{
public:

    DerivedClass() {}

    ~DerivedClass() override {}

    void fun( int a, int b = 111 ) override
    {
        BaseClass::fun( a, b );
    }
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    BaseClass *bc = new DerivedClass();
    bc->fun( 0 );

    DerivedClass *dc = dynamic_cast<DerivedClass*>( bc );
    dc->fun( 0 );


    return 0;
}
