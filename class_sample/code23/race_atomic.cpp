#include <thread>
#include <chrono>
#include <string>
#include <iostream>

#include <atomic> //<------ include atomic types

std::atomic_bool lock = ATOMIC_FLAG_INIT; // all threads share this 

void test_decrement(int * x){

  // test and set the lock
  do {
    while (lock) continue;
  } while (lock.exchange(true));
  // Note: exchange returns the value of the variable before the call.

  if(*x > 0) *x -= 1;

  lock.exchange(false);
}

void count(int * x)
{
  while(*x > 0){
    std::this_thread::sleep_for(std::chrono::nanoseconds(100000));
    test_decrement(x);
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
