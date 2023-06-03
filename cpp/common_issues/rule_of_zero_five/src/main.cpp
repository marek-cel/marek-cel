#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    int getVal() { return val_; }

    void setVal( int val ) { val_ = val; }

private:
    int val_ = 0;
};

////////////////////////////////////////////////////////////////////////////////

class B
{
public:

    B() = default;

    B( int val ) : val_ ( val ) {}

    int getVal() { return val_; }

    void setVal( int val ) { val_ = val; }

private:
    int val_ = 0;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    int val = 7;

    A a1;
    a1.setVal( val );
    std::cout << "line:" << __LINE__ << " " << a1.getVal() << std::endl;

    A a2( a1 );
    std::cout << "line:" << __LINE__ << " " << a2.getVal() << std::endl;

    A a3;
    std::cout << "dummy" << std::endl;
    val = 1;
    a3 = a1;
    std::cout << "line:" << __LINE__ << " " << a3.getVal() << std::endl;

    //////////////////

    B b1( val );
    std::cout << "line:" << __LINE__ << " " << b1.getVal() << std::endl;

    B b2( b1 );
    std::cout << "line:" << __LINE__ << " " << b2.getVal() << std::endl;

    B b3;
    std::cout << "dummy" << std::endl;
    val = 1;
    b3 = b1;
    std::cout << "line:" << __LINE__ << " " << b3.getVal() << std::endl;

    return 0;
}
