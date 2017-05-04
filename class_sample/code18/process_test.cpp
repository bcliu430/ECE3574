#include <iostream>

int main()
{
  std::cout << "code" << std::endl; 
  std::cout << (void*)(&main) << std::endl;

  std::cout << "stack" << std::endl; 
  int x,y,z;
  std::cout << (void*)(&x) << std::endl;
  std::cout << (void*)(&y) << std::endl;
  std::cout << (void*)(&z) << std::endl;

  std::cout << "heap" << std::endl; 
  int * a = new int;
  int * b = new int;
  int * c = new int;
  std::cout << (void*)(a) << std::endl;
  std::cout << (void*)(b) << std::endl;
  std::cout << (void*)(c) << std::endl;
  
}
