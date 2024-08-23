#include <chrono>
#include <iostream>
#include <thread>

void fun1(std::string name)
{
    std::cout << __func__ << " " << name << std::endl;
}

void fun2(std::string& name)
{
    std::cout << __func__ << " " << name << std::endl;
}

void fun3(std::string&& name)
{
    std::cout << __func__ << " " << name << std::endl;
}

void fun4(std::string* name)
{
    std::cout << __func__ << " " << (*name) << std::endl;
}

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    std::thread t1(fun1, "1");
    t1.join();

    std::string name2 = "2";
    std::thread t2(fun2, std::ref(name2));
    t2.join();

    std::string name3 = "3";
    std::thread t3(fun3, std::move(name3));
    t3.join();

    std::string name4 = "4";
    std::thread t4(fun4, &name4);
    t4.join();

    std::thread t5([](std::string name){
        std::cout << __func__ << " " << name << std::endl;
    }, "5");
    t5.join();

    return 0;
}
