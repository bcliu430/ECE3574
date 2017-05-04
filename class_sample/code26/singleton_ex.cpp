#include <iostream>

// this is NOT thread-safe
class Singleton
{
public:

  // do not allow copies
  Singleton(Singleton const&) = delete;
  void operator=(Singleton const&) = delete;
  
  static Singleton& getInstance()
  {
    static Singleton    instance;
    return instance;
  }

  void do_stuff(){
    std::cout << "Singleton::do_stuff()." << std::endl;
  }
  
private:
  Singleton() {}; //hide the constructor
  
};


void afunc()
{
  Singleton & instance = Singleton::getInstance();

  instance.do_stuff();

}

int main()
{

  Singleton & instance = Singleton::getInstance();

  instance.do_stuff();

  afunc();
  
  return 0;
}
