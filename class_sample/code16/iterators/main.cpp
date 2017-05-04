#include <algorithm>
#include <stdexcept>

#include <iostream>

#include "Vector.h"

int main()
{
  Vector<int> v(5);

  v[0] = 0;
  v[1] = 1;
  v[2] = 3;
  v[3] = 5;
  v[4] = 7;

  Vector<int>::Iterator it = v.begin();
  while( !it.isAtEnd() )
    {
      std::cout << it.get() << std::endl;
      it.next();
    }
  
  return 0;
}
