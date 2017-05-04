#include <algorithm>
#include <stdexcept>

#include <cassert>

#include <iostream>

// this is just a temporary hack to track allocations
//****************************************************
static unsigned long memused = 0;
void* operator new(std::size_t size) throw(std::bad_alloc)
{
    memused += size;
    return std::malloc(size);
}

void operator delete(void* ptr) throw()
{
    std::free(ptr);
}
//****************************************************


template <typename T>
class Vector
{
public:
  // default constructor
  Vector();

  // custom constructor
  Vector(std::size_t length);
  
  // copy constructor
  Vector(const Vector& x);
    
  // destructor
  ~Vector();
  
  // copy assignment
  Vector& operator=(Vector& x);
  
  // access
  T& operator[](std::size_t index);
  const T& operator[](std::size_t index) const;

  // length of the vector
  std::size_t length();
  
private:

  T * data;
  std::size_t len;
};

template <typename T>
Vector<T>::Vector()
{
  len = 3;
  data = new T[len];
}

template <typename T>
Vector<T>::Vector(std::size_t length)
{
  len = length;
  data = len ? new T[len] : nullptr;
}

template <typename T>
Vector<T>::Vector(const Vector<T> & x)
{
  len = x.len;
  data = len ? new T[len] : nullptr;
  std::copy(x.data, x.data + x.len, data);
}

template <typename T>
Vector<T>::~Vector()
{
  delete [] data;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector& x)
{
  if(this != &x)
    {
      if(len != x.len)
  	{
  	  delete [] data;
  	  len = x.len;
  	  data = len ? new T[len] : nullptr;
  	}
      std::copy(x.data, x.data + x.len, data);
    }
  return *this;
}

template <typename T>
T& Vector<T>::operator[](std::size_t index)
{
  if(index >= len) throw std::range_error("index out of bounds");
  
  return data[index];
}

template <typename T>
std::size_t Vector<T>::length()
{
  return len;
}
  
template <typename T>
const T& Vector<T>::operator[](std::size_t index) const
{
  if(index >= len) throw std::range_error("index out of bounds");
  
  return data[index];
}

int main()
{
  Vector<double> v;

  v[0] = 0.;
  v[1] = 1.1;
  v[2] = 3.14159;

  assert(v.length() == 3);
  
  const Vector<double> v2 = v;

  double x = v2[0];
  double y = v2[1];
  double z = v2[2];

  Vector<double> v3(100); 
    
  std::cout << memused << " total bytes allocated." << std::endl;
  
  return 0;
}
