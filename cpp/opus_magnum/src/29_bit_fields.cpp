#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class A
{
public:

    uint8_t f1 : 1;
    uint8_t f2 : 1;
    uint8_t f3 : 2;
    uint8_t f4 : 4;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;

    cout << sizeof(A) << endl;

    A a;

    a.f1 = 0b1;
    a.f2 = 0b1;
    a.f3 = 0b11;
    a.f4 = 0b1111;

    a.f1 = 0b11;    // warning!
    a.f2 = 0b11;    // warning!
    a.f3 = 0b111;   // warning!
    a.f4 = 0b11111; // warning!

    cout << (int)a.f1 << endl;
    cout << (int)a.f2 << endl;
    cout << (int)a.f3 << endl;
    cout << (int)a.f4 << endl;

    return 0;
}
