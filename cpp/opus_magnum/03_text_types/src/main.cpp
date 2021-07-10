#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    char str1[] = { u8"Zażółć gęślą jaźń." };
    wchar_t str2[] = { L"Zażółć gęślą jaźń." };

    std::cout << str1 << std::endl;
    std::wcout << str2 << std::endl;

    return 0;
}
