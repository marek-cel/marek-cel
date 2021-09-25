#include <iostream>
#include <memory>

#include "MyClassA.h"
#include "MyClassB.h"

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void funA()
{
    std::cout << "funA() 0" << std::endl;

    std::shared_ptr<MyClassA> mc1 = std::make_shared<MyClassA>();
    std::shared_ptr<MyClassA> mc2 = std::make_shared<MyClassA>();

    mc1->setPtr( mc2 );
    mc2->setPtr( mc1 );

    std::cout << "funA() 1" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void funB()
{
    std::cout << "funB() 0" << std::endl;

    std::shared_ptr<MyClassB> mc1 = std::make_shared<MyClassB>();
    std::shared_ptr<MyClassB> mc2 = std::make_shared<MyClassB>();

    mc1->setPtr( mc2 );
    mc2->setPtr( mc1 );

    std::cout << "funB() 1" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << "main() 0" << std::endl;

    funA();
    funB();

    std::cout << "main() 1" << std::endl;

    return 0;
}
