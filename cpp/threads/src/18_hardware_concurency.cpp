#include <iostream>
#include <thread>

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    std::cout << std::thread::hardware_concurrency() << std::endl;

    return 0;
}
