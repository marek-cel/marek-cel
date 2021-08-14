#include <iostream>
#include <bitset>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    uint8_t a = 0b00000001;
    uint8_t b = 0b00000011;

    uint8_t c1 = a & b;
    uint8_t c2 = a bitand b;

    uint8_t d1 = a | b;
    uint8_t d2 = a bitor b;

    uint8_t e1 = a ^ b;
    uint8_t e2 = a xor b;

    uint8_t f1 = ~a;
    uint8_t f2 = compl a;

    uint8_t g1 = a << 1;
    uint8_t g2 = b >> 1;
    int8_t  g3 = -1;
    int8_t  g4 = g3 >> 1; // zależy od implementacji

    cout << "a= " << std::bitset<8>(a) << endl;
    cout << "b= " << std::bitset<8>(b) << endl;

    cout << endl;

    cout << "c1= " << std::bitset<8>(c1) << endl;
    cout << "c2= " << std::bitset<8>(c2) << endl;

    cout << endl;

    cout << "d1= " << std::bitset<8>(d1) << endl;
    cout << "d2= " << std::bitset<8>(d2) << endl;

    cout << endl;

    cout << "e1= " << std::bitset<8>(e1) << endl;
    cout << "e2= " << std::bitset<8>(e2) << endl;

    cout << endl;

    cout << "f1= " << std::bitset<8>(f1) << endl;
    cout << "f2= " << std::bitset<8>(f2) << endl;

    cout << endl;

    cout << "g1= " << std::bitset<8>(g1) << endl;
    cout << "g2= " << std::bitset<8>(g2) << endl;
    cout << "g3= " << std::bitset<8>(g3) << endl;
    cout << "g4= " << std::bitset<8>(g4) << endl;

    return 0;
}
