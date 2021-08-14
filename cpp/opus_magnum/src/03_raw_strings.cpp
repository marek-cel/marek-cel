#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    char a[] = { R"(Hello \n World!)" };
    char b[] = { R"(Hello
                 World!)" };
    char c[] = { R"##(Hello " World!)##" };
    char d[] = { R"ogranicznik(Hello " World!)ogranicznik" };

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;

    return 0;
}
