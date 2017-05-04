// example adapted from Bartosz Milewski

#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <stdexcept>

std::string justa_function()
{
  std::string str = "Hello from the future";
  //throw std::logic_error("Exception in the future.");
  return str;
}

int main()
{
  std::future<std::string> fut = std::async(&justa_function);

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
  
  return 0;
}
