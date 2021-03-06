#pragma once

#include <vector>

#include "Command.h"

/** Invoker */
class MacroCommand : public Command
{
public:

    virtual void execute() override
    {
        for ( auto command : _commands )
        {
            command->execute();
        }
    }

    void addCommand( CommandPtr command )
    {
        _commands.push_back( command );
    }

private:

    std::vector< CommandPtr > _commands;
};
