#include "semaphore.h"

// this implementation allows 1 resource at a time
Semaphore::Semaphore(): n(1)
{}

int Semaphore::down()
{  
  std::unique_lock<std::mutex> lock(mutex);
  
  while(n <= 0){ // block until one resource available
    cond.wait(lock);
  }
  
  n--;
  
  return n;	
}

int Semaphore::up()
{
  std::unique_lock<std::mutex> lock(mutex);
  n++;
  cond.notify_all();
  
  return n;
}
