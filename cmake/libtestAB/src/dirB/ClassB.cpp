#include "ClassB.h"

#include <iostream>

ClassB::ClassB()
{
  std::cout << "ClassB::ClassB()" << std::endl;
}

ClassB::~ClassB()
{
  std::cout << "ClassB::~ClassB()" << std::endl;
}

int ClassB::fun() { return 'b'; }
