#pragma once

#include <iostream>
#include <memory>

class ReceiverA
{
public:

    void actionA()
    {
        std::cout << "ReceiverA::actionA()" << std::endl;
    }
};

using ReceiverAPtr = std::shared_ptr<ReceiverA>;
