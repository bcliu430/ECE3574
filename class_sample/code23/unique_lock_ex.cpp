#include <thread>
#include <mutex>
#include <algorithm>
#include <random>
#include <numeric>
#include <iostream>
#include <cassert>

// a typical use of deferred locking thread-safe rule-of-three
// in a vector-like object
class Foo
{
public:
  // default constructor
  Foo(): data(nullptr), size(0) {}

  // custom constructor
  Foo(std::size_t reserve): size(reserve) {
    data = new double[size];

    // fill it with the value size
    std::fill(data, data+size, double(size));
  }

  // copy constructor
  // I have to lock the one I am copying from
  Foo(const Foo& x){
    std::unique_lock<std::mutex> x_lock(x.the_mutex);

    // ok to copy now
    size = x.size;
    data = size ? new double[size] : nullptr;
    std::copy(x.data, x.data + x.size, data);

    // x_lock.unlock gets called when x_lock goes out of scope
    // and its destructor get called
  }
  
  // destructor
  ~Foo(){
    delete [] data; 
  }
  
  // copy assignment
  // I need to lock the mutex of the current object
  // and the one I am copying from
  Foo& operator=(const Foo& x){
    
    std::unique_lock<std::mutex> this_lock(the_mutex, std::defer_lock);
    std::unique_lock<std::mutex> x_lock(x.the_mutex, std::defer_lock);

    // lock both unique_locks, no deadlock guarantee
    std::lock(this_lock, x_lock);

    // ok to assign now
    std::cout << "Copy Assign" << std::endl;
    if(this != &x){
      delete data;
      size = x.size;
      data = size ? new double[size] : nullptr;
      //std::copy(x.data, x.data + x.size, data);
      for(std::size_t i = 0; i < size; ++i){
	std::cout << "Copy index " << i << " value " << x.data[i] << std::endl;
	data[i] = x.data[i];
      }
    }
    
    // unlocks occur when this_lock and x_lock go out of scope
    // and thier destructors get called

    return *this;
  }

  std::size_t getSize(){
    std::size_t rv;
    
    //std::unique_lock<std::mutex> this_lock(the_mutex);
    the_mutex.lock(); // replace with unique_lock to prevent deadlock
    rv = size;
    the_mutex.unlock(); // if used, this must be called

    return rv;
  }

  double get(std::size_t position){
    double rv;
    
    std::unique_lock<std::mutex> this_lock(the_mutex);
    rv = data[position];
    //this_lock.unlock();
    return rv;
  }
  
private:

  mutable std::mutex the_mutex;
  
  double * data;
  std::size_t size; 
};


void do_stuff(Foo & f)
{
  // setup random ints between 1 and 100
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> p(1,100);
  
  Foo local_foo(p(gen));

  f = local_foo;
}

int main()
{
  Foo myfoo;

  std::thread th1(do_stuff, std::ref(myfoo));
  std::thread th2(do_stuff, std::ref(myfoo));

  th1.join();
  th2.join();

  std::cout << myfoo.getSize() << std::endl;

  for(std::size_t i = 0; i < myfoo.getSize(); ++i){
    std::cout << myfoo.get(i) << std::endl;
    assert(myfoo.get(i) == myfoo.getSize());
  }
    
  return 0;
}
