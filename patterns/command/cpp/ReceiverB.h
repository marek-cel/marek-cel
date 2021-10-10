#pragma once

#include <iostream>
#include <memory>

class ReceiverB
{
public:

    void actionB()
    {
        std::cout << "ReceiverB::actionB()" << std::endl;
    }
};

using ReceiverBPtr = std::shared_ptr<ReceiverB>;
