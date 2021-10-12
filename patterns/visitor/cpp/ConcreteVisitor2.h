#pragma once

#include <iostream>

#include "ConcreteElementA.h"
#include "ConcreteElementB.h"
#include "Visitor.h"

class ConcreteVisitor2 : public Visitor
{
public:

    void visitConcreteElementA (ConcreteElementA *elementA)
    {
        std::cout << "ConcreteVisitor2::visitConcreteElementA(ConcreteElementA*)" << std::endl;
        elementA->operationA();
    }

    void visitConcreteElementB (ConcreteElementB *elementB)
    {
        std::cout << "ConcreteVisitor2::visitConcreteElementB(ConcreteElementB*)" << std::endl;
        elementB->operationB();
    }
};

