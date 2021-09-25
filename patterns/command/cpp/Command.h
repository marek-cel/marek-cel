#pragma once

#include <memory>

class Command
{
public:

    virtual void execute() = 0;
};

using CommandPtr = std::shared_ptr<Command>;
