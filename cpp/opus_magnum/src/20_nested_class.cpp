#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

class A
{
public:

    class Twew
    {
    public:

        void fun( A *a )
        {
            a->_a = 1;
        }

    private:

        int _b {};
    };

    void funA()
    {
        Twew twew;

        //twew._b = 1; // error!

        twew.fun( this );
    }

private:

    int _a {};
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    A a;
    a.funA();

    return 0;
}
