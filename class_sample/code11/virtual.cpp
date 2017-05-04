#include <iostream>

class BaseClass
{
public:

  virtual void doit() {
    std::cout << "Base" << std::endl;
  };
  
};

class DerivedClass: public BaseClass
{
public:

  void doit() {
    std::cout << "Derived" << std::endl;
  };
};

int main()
{
  DerivedClass d;

  d.doit();

  BaseClass * b = &d;

  b->doit();

  BaseClass btemp;
  btemp.doit();
  
  return 0;
}
