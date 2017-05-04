// example from Bartosz Milewski

#include <iostream>
#include <string>
#include <thread>
#include <future>

void thread_function(std::promise<std::string> & p)
{
  std::string str = "Hello from the future";
  p.set_value(str);
}


int main()
{
  std::promise<std::string> prom;
  std::future<std::string> fut = prom.get_future();

  std::thread th(&thread_function, std::ref(prom));

  std::cout << "In main." << std::endl;
  
  std::string value = fut.get(); // this blocks until the future is "ready"
  
  std::cout << "Message from the future: " << value << std::endl;

  th.join();
  
  return 0;
}
