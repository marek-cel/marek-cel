#pragma once

#include <iostream>

#include "ConcreteElementA.h"
#include "ConcreteElementB.h"
#include "Visitor.h"

class ConcreteVisitor1 : public Visitor
{
public:

    void visitConcreteElementA (ConcreteElementA *elementA)
    {
        std::cout << "ConcreteVisitor1::visitConcreteElementA(ConcreteElementA*)" << std::endl;
        elementA->operationA();
    }

    void visitConcreteElementB (ConcreteElementB *elementB)
    {
        std::cout << "ConcreteVisitor1::visitConcreteElementB(ConcreteElementB*)" << std::endl;
        elementB->operationB();
    }
};

