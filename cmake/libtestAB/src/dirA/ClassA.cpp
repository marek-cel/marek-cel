#include "ClassA.h"

#include <iostream>

ClassA::ClassA()
{
  std::cout << "ClassA::ClassA()" << std::endl;
}

ClassA::~ClassA()
{
  std::cout << "ClassA::~ClassA()" << std::endl;
}

int ClassA::fun() { return 'a'; }
