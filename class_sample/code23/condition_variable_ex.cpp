#include <thread>
#include <mutex>
#include <condition_variable>

bool something_happened;
std::mutex the_mutex;
std::condition_variable the_condition;

void thread1()
{
  std::unique_lock<std::mutex> lock(the_mutex);
  while(!something_happened){
    the_condition.wait(lock);
  }
}

void thread2()
{
  // pretend we did some work
  std::unique_lock<std::mutex> lock(the_mutex);
  something_happened = true;
  the_condition.notify_one();
}

int main()
{    
  std::thread t1(thread1);
  std::thread t2(thread2);

  t1.join();
  t2.join();
  
  return 0;
}

