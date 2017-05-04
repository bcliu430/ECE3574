#include <iostream>
#include <thread>
#include <string>

void print(std::string name)
{
  std::cout << name << " running in thread "
	    << std::this_thread::get_id() << std::endl;
}

int main()
{
  using namespace std;

  std::string name1 = "Sue";
  std::string name2 = "Bob";

  
  cout << "Running in main thread " << this_thread::get_id() << endl;
    
  thread th1(print, name1);
  thread th2(print, name2);

  th1.join();
  th2.join();

  return 0;
}
