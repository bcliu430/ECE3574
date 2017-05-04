
// this would be defined in a header
#include <cstdlib>
namespace embed
{
    template<typename T, std::size_t N>
    struct stack
    {

	stack(): top(0) {};
		
	bool empty(){
	    return (top == 0);
	}
    
	bool push(const T& value){
	    if(top >= N) return false;
	    
	    data[top] = value;
	    ++top;

	    return true;
	}
    
	bool pop(){
	    if(top == 0) return false;
	    --top;
	    return true;
	}
    
	bool peek(T& value){
	    if(top == 0) return false;
	    value = data[top-1];
	    return true;
	}
	
	static T data[N];
	long int top;
    };

    template<typename T, std::size_t N>
    T stack<T,N>::data[N]; 
}

// this might be a unit test that runs outside the target platform
#include <cassert>
int main()
{
    const std::size_t N = 100;
    
    embed::stack<int,N> mys;
    
    bool rv;
    for(std::size_t i = 0; i < N; ++i){
	rv = mys.push(static_cast<int>(i));
	assert(rv);
	int value;
	rv = mys.peek(value);
	assert(rv);
	assert(value == i);
    }
    rv = mys.push(1);
    assert(!rv);

    for(std::size_t i = 0; i < N; ++i){
	int value;
	rv = mys.peek(value);
	assert(rv);
	assert(value == N-i-1);

	rv = mys.pop();
	assert(rv);

    }
    rv = mys.pop();
    assert(!rv);

    return 0;
}
