#include <iostream>
#include <memory>

#include "Client.h"
#include "ConcreteFactory1.h"

int main( int argc, char *argv[] )
{
    std::shared_ptr<ConcreteFactory1> cf1 = std::make_shared<ConcreteFactory1>();
    std::shared_ptr<Client> client = std::make_shared<Client>( cf1 );

    client->doSomething();

    return 0;
}
