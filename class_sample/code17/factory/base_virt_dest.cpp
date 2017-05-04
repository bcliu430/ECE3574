#include <iostream>

class Base
{
public:
  Base(){
    std::cout << "Base: Constructor" << std::endl;
  }
  // this SHOULD be virtual
  ~Base(){
    std::cout << "Base: Destructor" << std::endl;
  }

  virtual void doit(){
    std::cout << "Base: doit()" << std::endl;
  }
};

class Derived: public Base
{
public:
  Derived(int N){
    std::cout << "Derived: Constructor" << std::endl;
    resource = new float[N];
  }
  
  // if you write this for a derived class
  // check the base class has a virtual destructor
  ~Derived(){
    std::cout << "Derived: Destructor" << std::endl;
    delete [] resource;
  }
  void doit(){
    std::cout << "Derived: doit()" << std::endl;
  }
  
private:
  float * resource;
};

int main(){

  Derived *objp = new Derived(10);
  Base * bp = objp; // up-cast

  bp->doit();

  delete bp; // which destructor(s) get called?
  
  return 0;
}
