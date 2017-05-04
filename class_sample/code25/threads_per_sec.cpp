#include <thread>
#include <future>
#include <chrono>
#include <iostream>

void thread_func()
{
  // do nothing
  volatile int i = 0;
}

int main()
{
  std::size_t N = 100000;
  
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;

  // time N thread creates
  start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < N; ++i)
  {
    std::thread th(&thread_func);
    th.join();
  }
  end = std::chrono::system_clock::now();
  
  elapsed_seconds = end-start;
  std::cout << N <<  " threads in " << elapsed_seconds.count() << " seconds." << std::endl;
  std::cout << static_cast<double>(N)/elapsed_seconds.count() <<  " threads per second." << std::endl;
  std::cout << 1000*elapsed_seconds.count()/static_cast<double>(N) <<  " milliseconds per thread." << std::endl;

  std::cout << std::endl;

  // time N function calls
  start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < N; ++i)
  {
    thread_func();
  }
  end = std::chrono::system_clock::now();
  
  elapsed_seconds = end-start;
  std::cout << N <<  " calls in " << elapsed_seconds.count() << " seconds." << std::endl;
  std::cout << static_cast<double>(N)/elapsed_seconds.count() <<  " calls per second." << std::endl;
  std::cout << 1000*elapsed_seconds.count()/static_cast<double>(N) <<  " milliseconds per call." << std::endl;

  
  return 0;
}
