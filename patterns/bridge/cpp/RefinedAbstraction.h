#pragma once

#include "Abstraction.h"

class RefinedAbstraction : public Abstraction
{
public:

    RefinedAbstraction( std::shared_ptr<Implementator> imp ) : Abstraction( imp ) {}
};

