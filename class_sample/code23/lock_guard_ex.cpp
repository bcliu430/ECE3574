#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <stdexcept>

std::mutex the_mutex;

void print(std::string what)
{
  try{
    std::lock_guard<std::mutex> guard(the_mutex);
    std::cout << what << std::endl;
    throw std::logic_error("An exception occurred!");
    // no unlock required
  }
  catch(std::exception& ex)
    {
      // handle the exception
    }
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
