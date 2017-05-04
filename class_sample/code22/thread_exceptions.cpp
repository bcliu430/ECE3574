// example from Bartosz Milewski

#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <stdexcept>

void thread_function(std::promise<std::string> & p)
{
  try{
    std::string str = "Hello from the future";
    throw std::logic_error("Exception in the future.");
    p.set_value(str);
  }
  catch(...){
    p.set_exception(std::current_exception());
  }
}

int main()
{
  std::promise<std::string> prom;
  std::future<std::string> fut = prom.get_future();

  std::thread th(&thread_function, std::ref(prom));

  std::cout << "In main." << std::endl;

  try{
    // this blocks until the future is "ready"
    // if an exption is set on the promise, this throws
    std::string value = fut.get();
    
    std::cout << "Message from the future: " << value << std::endl;
  }
  catch(std::exception & ex){
    std::cout << "Message from the future: " << ex.what() << std::endl;
  }

  th.join();
  
  return 0;
}
