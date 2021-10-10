#pragma once

#include <memory>

#include "ConcreteCommandA.h"
#include "ConcreteCommandB.h"

#include "ReceiverA.h"
#include "ReceiverB.h"

#include "MacroCommand.h"

class Client
{
public:

    void doSomething()
    {
        ReceiverAPtr ra = std::make_shared<ReceiverA>();
        ReceiverBPtr rb = std::make_shared<ReceiverB>();

        CommandPtr ca = std::make_shared<ConcreteCommandA>( ra );
        CommandPtr cb = std::make_shared<ConcreteCommandB>( rb );

        std::unique_ptr<MacroCommand> macro = std::make_unique<MacroCommand>();

        macro->addCommand( ca );
        macro->addCommand( cb );

        macro->execute();
    }
};

