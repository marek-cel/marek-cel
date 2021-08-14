#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void fun1()
{
    cout << __func__ << endl;
//    bad_alloc e;
//    throw( e );
}

////////////////////////////////////////////////////////////////////////////////

void fun2() noexcept
{
    cout << __func__ << endl;
//    bad_alloc e;
//    throw( e );
}

////////////////////////////////////////////////////////////////////////////////

void fun3() noexcept( 3 < 2 )
{
    cout << __func__ << endl;
//    bad_alloc e;
//    throw( e );
}

////////////////////////////////////////////////////////////////////////////////

void fun4() noexcept( 3 > 2 )
{
    cout << __func__ << endl;
    bad_alloc e;
    throw( e );
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    constexpr bool b1 = noexcept( fun1() );
    constexpr bool b2 = noexcept( fun2() );
    constexpr bool b3 = noexcept( fun3() );
    constexpr bool b4 = noexcept( fun4() );

    if ( b1 ) cout << "b1 jest noexcept" << endl;
    else      cout << "b1 NIE jest noexcept" << endl;

    if ( b2 ) cout << "b2 jest noexcept" << endl;
    else      cout << "b2 NIE jest noexcept" << endl;

    if ( b3 ) cout << "b3 jest noexcept" << endl;
    else      cout << "b3 NIE jest noexcept" << endl;

    if ( b4 ) cout << "b4 jest noexcept" << endl;
    else      cout << "b4 NIE jest noexcept" << endl;

    try
    {
        fun1();
        fun2();
        fun3();
        fun4();
    }
    catch ( std::exception &e )
    {
        cout << e.what() << endl;
    }
    catch ( ... )
    {
        cout << "Unknown exception." << endl;
    }

    return 0;
}
