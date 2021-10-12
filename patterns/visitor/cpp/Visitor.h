#pragma once

class ConcreteElementA;
class ConcreteElementB;

class Visitor
{
public:

    virtual void visitConcreteElementA (ConcreteElementA *elementA) = 0;
    virtual void visitConcreteElementB (ConcreteElementB *elementB) = 0;
};

