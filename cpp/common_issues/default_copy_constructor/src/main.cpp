#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    A()
    {
        val_ = new int [10];
    }

    A( const A& a)
    {
        val_ = new int [10];

        for ( int i = 0; i < 10; i++ )
        {
            val_[i] = a.val_[i];
        }
    }

    ~A()
    {
        if ( val_ ) delete val_;
        val_ = nullptr;
    }

    A& operator=( const A& a)
    {
        for ( int i = 0; i < 10; i++ )
        {
            val_[i] = a.val_[i];
        }

        return *this;
    }

    int* val_ = nullptr;
};

////////////////////////////////////////////////////////////////////////////////

class B
{
public:

    A a_;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    B b1;

    for ( int i = 0; i < 10; i++ )
    {
        b1.a_.val_[i] = i + 1;
    }

    B b2;
    b2 = b1;

    for ( int i = 0; i < 10; i++ )
    {
        b1.a_.val_[i] = i + 11;
    }

    std::cout << "b1" << std::endl;
    for ( int i = 0; i < 10; i++ )
    {
        std::cout << b1.a_.val_[i] << "\t";
    }
    std::cout << std::endl;

    std::cout << "b2" << std::endl;
    for ( int i = 0; i < 10; i++ )
    {
        std::cout << b2.a_.val_[i] << "\t";
    }
    std::cout << std::endl;






    return 0;
}
