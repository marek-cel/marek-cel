#include <chrono>
#include <iostream>
#include <thread>

#include <vector>
#include <string>

void fizzbuzz()
{
    std::vector<std::string> children {
        "Abdul",
        "Bart",
        "Claudia",
        "Divya"
    };
    int i_child = 0;

    for ( int i = 1; i < 16; ++i )
    {
        std::cout << children[i_child] << " says ";

        if ( i % 3 == 0 && i % 5 == 0 )
        {
            std::cout << "fizzbuzz";
        }
        else if ( i % 3 == 0 )
        {
            std::cout << "fizz";
        }
        else if ( i % 5 == 0 )
        {
            std::cout << "buzz";
        }
        else
        {
            std::cout << i;
        }

        std::cout << std::endl;

        i_child++;
        if ( i_child > 3 ) i_child = 0;
    }
}

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    std::thread t1(fizzbuzz);
    t1.join();

    return 0;
}
