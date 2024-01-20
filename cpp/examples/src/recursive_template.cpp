#include <iostream>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void print()
{
    std::cout << std::endl;
}

template<typename T, typename... Args>
std::vector<double> print(T first, Args... args)
{
    std::cout << first << " ";
    print(args...);
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    cout << "Hello World!" << endl;

    print(1, 2.5, "Hello", 'a');

    return 0;
}
