
#ifndef _POOL_H_
#define _POOL_H_

#include "ring_buffer.h"

#include <cstdint> 
namespace embed
{
    template<typename T, std::uint32_t N>
    class pool
    {	  
    public:	
	pool(){ // all blocks are free
	    for(std::uint32_t i = 0; i < N; ++i){
		freeq.enqueue(data+i);
	    }
	}

	// get an unused block, return null if none
	T* alloc(){
	    T* ptr;
	    if(freeq.dequeue(ptr)){
		return ptr;
	    }
	    return 0;
	}

	// return a block to the pool
	void free(T* block_ptr){
	    // check if already in queue
	    if(!freeq.exists(block_ptr)){
		// if not put into free queue
		freeq.enqueue(block_ptr);
	    }
	}

	// how many blocks are available
	std::uint32_t available(){
	    return freeq.size();
	}
	
    private:	
	T data[N];

	// queue of free blocks
	RingBuffer<T*,N> freeq;
    };
}

#endif // _POOL_H_
