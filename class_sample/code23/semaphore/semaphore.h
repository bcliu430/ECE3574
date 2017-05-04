
#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:

  // default constuctor
  Semaphore(); 

  // default destructor
  ~Semaphore() = default; 
  
  // Decrement Semaphore, blocks until resource is available
  int down();
  
  // Increment Semaphore
  int up();
  
private:
  int n;
  std::mutex mutex;
  std::condition_variable cond;
};

#endif // _SEMAPHORE_H_

