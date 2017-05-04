#include <thread>
#include <chrono>
#include <string>
#include <iostream>

void count(int * x)
{
  while(*x > 0){
    //std::this_thread::sleep_for(std::chrono::nanoseconds(100));
    *x -=1;
  }
}

int main()
{
  int x = 1000;
  
  std::thread t1(count, &x);
  std::thread t2(count, &x);
  std::thread t3(count, &x);
  std::thread t4(count, &x);
  std::thread t5(count, &x);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();

  std::cout << "x = " << x << std::endl; 
  
  return 0;
}
