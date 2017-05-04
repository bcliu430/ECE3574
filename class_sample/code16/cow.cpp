#include <algorithm>
#include <stdexcept>

#include <iostream>

static unsigned long memused = 0;

void* operator new(std::size_t size)
{
  memused += size;
  //std::printf("global op new called, total size = %zu\n",memused);
  return std::malloc(size);
}

void operator delete(void* ptr) throw()
{
    std::free(ptr);
}

template <typename T>
class Vector
{
public:
  // default constructor
  Vector();
  
  // copy constructor
  Vector(const Vector& x);
    
  // destructor
  ~Vector();
  
  // copy assignment
  Vector& operator=(Vector& x);
  
  // normal access via index operator
  T& operator[](std::size_t index);
  const T& operator[](std::size_t index) const;

  // more fine grained access using methods
  T get(std::size_t index) const;
  void set(std::size_t index, const T& value );
  
private:

  T * data;
  std::size_t length;
  bool iscopy;
};

template <typename T>
Vector<T>::Vector()
{
  length = 3;
  data = new T[length];
  iscopy = false;
}

template <typename T>
Vector<T>::Vector(const Vector<T> & x)
{
  length = x.length;
  data = x.data;
  iscopy = true;
  //std::cout << "Shallow Copy" << std::endl;
  //data = new T[length];
  //std::copy(x.data, x.data + x.length, data);
}

template <typename T>
Vector<T>::~Vector()
{
  if(!iscopy)
    {
      delete [] data;
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector& x)
{
    if(this != &x)
    {
      if(!iscopy) delete [] data;
      length = x.length;
      data = x.data;
      iscopy = true;
      //std::cout << "Shallow Copy" << std::endl;
    }
  // if(this != &x)
  //   {
  //     if(length != x.length)
  // 	{
  // 	  delete [] data;
  // 	  length = x.length;
  // 	  data = new T[length];
  // 	}
  //     std::copy(x.data, x.data + x.length, data);
  //   }
  return *this;
}

template <typename T>
T& Vector<T>::operator[](std::size_t index)
{
  if(index >= length) throw std::range_error("index out of bounds");

  if(iscopy) // trigger copy before returning
    {
      //std::cout << "Copying" << std::endl;
      T * newdata = new T[length];
      std::copy(data, data + length, newdata);
      data = newdata;
      iscopy = false;
    }
  
  return data[index];
}

template <typename T>
const T& Vector<T>::operator[](std::size_t index) const
{
  if(index >= length) throw std::range_error("index out of bounds");
  
  return data[index];
}

template <typename T>
T Vector<T>::get(std::size_t index) const
{
  if(index >= length) throw std::range_error("index out of bounds");
  
  return data[index];
}

template <typename T>
void Vector<T>::set(std::size_t index, const T& value )
{
  if(index >= length) throw std::range_error("index out of bounds");

  if(iscopy) // trigger copy before setting
    {
      T * newdata = new T[length];
      std::copy(data, data + length, newdata);
      data = newdata;
      iscopy = false;
    }
  
  data[index] = value;
}

int main()
{
  Vector<double> v;

  v[0] = 0.;
  v[1] = 1.1;
  v[2] = 3.14159;

  Vector<double> v2 = v; // make const

  double x = v2[0];
  double y = v2[1];
  double z = v2[2];

  // double x = v2.get(0);
  // double y = v2.get(1);
  // double z = v2.get(2);

  //v2.set(0, z);
  
  std::cout << memused << " total bytes allocated." << std::endl;
    
  return 0;
}

