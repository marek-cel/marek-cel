#include <iostream>

#include <BaseClass.h>
#include <DerivedClass.h>

////////////////////////////////////////////////////////////////////////////////

int main()
{
    BaseClass    *bc = new DerivedClass;
    DerivedClass *dc = new DerivedClass;

    std::cout << bc->getOne() << std::endl;
    std::cout << bc->getTwo() << std::endl;

    std::cout << dc->getOne() << std::endl;
    std::cout << dc->getTwo() << std::endl;

    delete bc;
    delete dc;

    return 0;
}
