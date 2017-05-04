#include "Interface.h"

class InterfacePrivate
{
public:

  void doSomething(){};
};
  
Interface::Interface(): pimpl(new InterfacePrivate)
{
}


Interface::~Interface()
{
  // note we do not need to do anything here because of the use of
  // unique_ptr
}

void Interface::doSomething()
{
  // forward the request to the private implementation
  pimpl->doSomething();
}
