#include <iostream>
#include <thread>

void print()
{
  std::cout << "Running in thread " << std::this_thread::get_id() << std::endl;
}

int main()
{
  using namespace std;

  cout << "Running in main thread " << this_thread::get_id() << endl;
    
  thread th1(&print);
  thread th2(&print);

  th1.join();
  th2.join();

  return 0;
}
