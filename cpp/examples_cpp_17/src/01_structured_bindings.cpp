#include <iostream>

#include <map>
#include <string>

using namespace std;

struct MyStruct
{
    std::string n;
    double x;
};

int main()
{
    cout << __cplusplus << endl;

    int a[3] = {1, 2, 3};
    auto [x, y, z] = a;
    std::cout << x << " " << y << " " << z << std::endl;

    std::map<int, std::string> my_map;
    my_map.insert(std::pair<int,std::string>(1, "one"));
    my_map.insert(std::pair<int,std::string>(2, "two"));

    for ( auto [i, name] : my_map )
    {
        std::cout << i << " " << name << std::endl;
    }

    MyStruct ms;
    ms.n = "pi";
    ms.x = 3.14;
    auto [name, value] = ms;
    std::cout << name << " " << value << std::endl;

    return 0;
}
