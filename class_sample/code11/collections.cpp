#include <iostream>
#include <vector>

struct Base
{
  virtual void print() = 0;
};

struct Derived1: public Base
{
  void print()
  {
    std::cout << "Derived 1" << std::endl;
  }
};

struct Derived2: public Base
{
  void print()
  {
    std::cout << "Derived 2" << std::endl;
  }
};

int main()
{
  std::vector< Base *> collection;

  Derived1 d1;
  Derived2 d2;

  collection.push_back(&d1);
  collection.push_back(&d2);

  for(std::vector< Base *>::iterator it = collection.begin();
      it != collection.end();
      ++it)
    {
      (*it)->print();
    }

  return 0;
}
