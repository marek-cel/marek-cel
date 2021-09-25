#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class MyClass
{
public:

    MyClass( int i ) :
        _i ( i )
    {
        cout << "MyClass() " << _i << endl;
    }

    ~MyClass()
    {
        cout << "~MyClass() " << _i << endl;
    }

private:
    const int _i;
};

////////////////////////////////////////////////////////////////////////////////

class Storage
{
public:

    Storage()
    {
        _mc1 = std::make_shared< MyClass >( 1 );
        _mc2 = std::make_shared< MyClass >( 2 );
    }

    std::shared_ptr< MyClass > getMC1() { return _mc1; }

private:

    std::shared_ptr< MyClass > _mc1;
    std::shared_ptr< MyClass > _mc2;
};

////////////////////////////////////////////////////////////////////////////////

void test1()
{
    cout << endl << __func__ << endl;

    Storage *s = new Storage();

    cout << __FILE__ << "(" << __LINE__ << ")" << endl;

    std::shared_ptr< MyClass > mc1 = s->getMC1();

    delete s;

    cout << __FILE__ << "(" << __LINE__ << ")" << endl;
}

////////////////////////////////////////////////////////////////////////////////

void test2()
{
    cout << endl << __func__ << endl;

    std::shared_ptr< MyClass > mc1 = std::make_shared< MyClass >( 1 );
    std::shared_ptr< MyClass > mc2 = std::make_shared< MyClass >( 2 );

    cout << __FILE__ << "(" << __LINE__ << ")" << endl;

    mc1 = nullptr;

    cout << __FILE__ << "(" << __LINE__ << ")" << endl;
}

////////////////////////////////////////////////////////////////////////////////

void test3()
{
    cout << endl << __func__ << endl;

    std::shared_ptr< MyClass > mc1;

    if ( mc1 )
        cout << "mc1 is NOT null" << endl;
    else
        cout << "mc1 is null" << endl;

    if ( !mc1 )
        cout << "mc1 is null" << endl;
    else
        cout << "mc1 is NOT null" << endl;

    if ( mc1 == nullptr )
        cout << "mc1 is null" << endl;
    else
        cout << "mc1 is NOT null" << endl;

    if ( mc1 != nullptr )
        cout << "mc1 is NOT null" << endl;
    else
        cout << "mc1 is null" << endl;

    mc1 = std::make_shared< MyClass >( 0 );

    if ( mc1 )
        cout << "mc1 is NOT null" << endl;
    else
        cout << "mc1 is null" << endl;

    if ( !mc1 )
        cout << "mc1 is null" << endl;
    else
        cout << "mc1 is NOT null" << endl;

    if ( mc1 == nullptr )
        cout << "mc1 is null" << endl;
    else
        cout << "mc1 is NOT null" << endl;

    if ( mc1 != nullptr )
        cout << "mc1 is NOT null" << endl;
    else
        cout << "mc1 is null" << endl;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    test1();
    test2();
    test3();

    return 0;
}
