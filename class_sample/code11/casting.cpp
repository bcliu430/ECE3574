#include <iostream>

struct Base
{
  virtual void doit(){
    std::cout << "Base" << std::endl;
  }
};

class Derived: public Base
{
public:
  void doit(){
    std::cout << "Derived" << std::endl;
  }
};


int main()
{

  Derived d;
  Base b;
  
  Base * bpd = &d;
  Base * bpb = &b;


  if( Derived *dp = dynamic_cast<Derived *>(bpd) )
    {
      std::cout << "down-cast successful :-)" << std::endl;
      dp->doit();
    }
  else
    {
      std::cout << "down-cast failed :-(" << std::endl;
    }
  
  if( Derived *dp = dynamic_cast<Derived *>(bpb) )
    {
      std::cout << "down-cast successful" << std::endl;
      dp->doit();
    }
  else
    {
      std::cout << "down-cast failed :-(" << std::endl;
    }
  
  return 0;
}
