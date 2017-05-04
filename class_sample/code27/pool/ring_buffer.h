// implement a deque as a ring buffer
// enqueue is O(1)
// dequeue is O(1)
// exists is O(n)
//
// might be better to use a priority queue:
// enqueue is O(log n)
// dequeue is O(log n)
// exists is O(log n)
 
#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#include <cstdlib>

namespace embed
{
template <typename T, std::size_t N>
class RingBuffer
{  
public:
    RingBuffer(){
	front = 0;
	back = N-1;
	count = 0;
    }
    
    bool enqueue(const T& item){
	if(count != N){
	    back = (back + 1) % N;
	    data[back] = item;
	    ++count;
	    return true;
	}
	
	return false;
    }
    
    bool dequeue(T& value){
	if(count > 0){
	    value = data[front];
	    front = (front +1) % N;
	    --count;
	    return true;
	}
	return false;
    }

    bool exists(const T& item){
	for(int i = 0, j = front; i < count; ++i, j = (front + 1) % N){
	    if(item == data[j]) return true;
	}
	return false;
    }
    
    long int size(){
	return count;
    }
  
private:
    
    long int front;
    long int back;
    long int count;
    
    T data[N];
};
}
#endif // _RING_BUFFER_H_
