#include <thread>
#include <iostream>

#include "semaphore.h"

Semaphore sem;

void print(std::string what)
{
  sem.down();
  std::cout << what << std::endl;
  sem.up();
}

int main()
{
  std::string msg1 = "I am the first message";
  std::string msg2 = "I am the second message";
  std::string msg3 = "I am the third message.";
    
  std::thread t1(print, msg1);
  std::thread t2(print, msg2);
  std::thread t3(print, msg3);

  t1.join();
  t2.join();
  t3.join();
  
  return 0;
}
