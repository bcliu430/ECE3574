#include <iostream>
#include <cassert>

#include "shared_ring_buffer.h"

int main(int argc, char *argv[])
{
  SharedRingBuffer<int> buffer;
  int value;

  buffer.create(100);

  while(true){
    if(buffer.getCount() == 0){
      std::cout << "enter a value: ";
      std::cin >> value;
      buffer.enqueue(value);
      std::cout << "Enqueued: " << value << std::endl;
      if( value == 0){
          break;
      }
    }
  }

  return 0;
}
