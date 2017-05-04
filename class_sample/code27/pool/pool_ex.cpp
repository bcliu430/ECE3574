// NOTE: the assertions below are just for testing
#include <cassert>

#include "pool.h"

int main()
{
    const std::uint32_t BLOCKSIZE = 100;
    
    embed::pool<int,BLOCKSIZE> p; 
    
    int * new_ptr = p.alloc();
    assert(p.available() == 99);

    // here we might use the object

    // we are done, free it
    p.free(new_ptr);
    assert(p.available() == 100);
    
    return 0;
}
