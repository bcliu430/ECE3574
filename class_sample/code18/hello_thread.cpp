#include <iostream>
#include <thread>

void print()
{
  std::cout << "Running in thread " << std::this_thread::get_id() << std::endl;
}

int main()
{
  using namespace std;

  thread th1(&print);
  thread th2(&print);

  cout << "Running in main thread" << endl;

  th1.join();
  th2.join();

  return 0;
}
