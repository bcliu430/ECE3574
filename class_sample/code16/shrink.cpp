#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

int main()
{
  std::vector<int> c;
  std::cout << "Default capacity is " << c.capacity() << std::endl;

  c.resize(100);
  std::cout << "Capacity after resizing to 100 is " << c.capacity() << std::endl;

  c.clear();
  std::cout << "Capacity after clear is " << c.capacity() << std::endl;

  c.shrink_to_fit();
  //std::vector<int>(c).swap(c);
  std::cout << "Capacity after shrink is " << c.capacity() << std::endl;

  std::list<int> mylist;
  mylist.push_back(0);
  mylist.push_back(12);
  mylist.push_back(31);
  std::cout << mylist.size() << std::endl;

  mylist.erase(std::remove(mylist.begin(), mylist.end(), 12), mylist.end());
  std::cout << mylist.size() << std::endl;
  
  return 0;
}
