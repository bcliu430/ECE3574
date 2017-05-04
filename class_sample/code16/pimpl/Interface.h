
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <memory> // for std::unique_ptr

// forward declare the private implementation
class InterfacePrivate;

class Interface
{
public:
  Interface();
  ~Interface();

  void doSomething();
  
private:

  std::unique_ptr<InterfacePrivate> pimpl;
};

#endif // _INTERFACE_H_
