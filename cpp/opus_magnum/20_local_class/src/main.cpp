#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void fun()
{
    class A
    {
    public:

        void method()
        {
            cout << "A::method()" << endl;
        }

        //void method2();
    };

    A a;
    a.method();
}

// error!
//void A::method2()
//{
//    cout << "A::method()" << endl;
//}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    fun();

    // A a;        // error!
    // a.method(); // error!

    return 0;
}
