#include <algorithm>
#include <stdexcept>

#include <iostream>

// I have simlified Vector here to make the point clearer
template <typename T>
class Vector
{
public:
  // default constructor
  Vector();

  // custom constructor
  Vector(std::size_t len);
  
  // copy constructor
  Vector(const Vector& x);
    
  // destructor
  ~Vector();
  
  // copy assignment
  Vector& operator=(Vector x);
  
  // a swap method
  void swap(Vector& a, Vector& b);

  // we add a move constructor
  Vector(Vector&& x);

  // get the size
  std::size_t size();
  
private:
  
  T * data;
  std::size_t length;
};

template <typename T>
Vector<T>::Vector()
{
  length = 3;
  data = new T[length];
}

template <typename T>
Vector<T>::Vector(std::size_t len)
{
  length = len;
  data = new T[length];
}

template <typename T>
Vector<T>::Vector(const Vector<T> & x)
{
  std::cout << "Copy Construct" << std::endl;
    
  length = x.length;
  data = length ? new T[length] : nullptr;
  std::copy(x.data, x.data + x.length, data);
}

template <typename T>
Vector<T>::~Vector()
{
  delete [] data;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector x)
{
  swap(*this, x);
  
  return *this;
}


template <typename T>
void Vector<T>::swap(Vector<T>& a, Vector<T>& b)
{
  std::swap(a.length, b.length);
  std::swap(a.data, b.data);
}

// we implement the move contructor
template <typename T>
Vector<T>::Vector(Vector<T>&& x): Vector() // construct with default
{
  std::cout << "Move Construct" << std::endl;
  
  swap(*this, x); // swap the contents
}

template <typename T>
std::size_t Vector<T>::size()
{
  return length;
}

class Foo{
public:
  
  void setVector(Vector<double> &v){
    insidev = std::move(v);
  }

  void print(){
    std::cout << "Inside Foo size " << insidev.size() << std::endl;
  }
  
private:

  Vector<double> insidev;
};

int main()
{
  Vector<double> v(10);
  Foo f;
  f.print();
  
  std::cout << v.size() << std::endl;
    
  f.setVector(v);

  std::cout << v.size() << std::endl;

  f.print();
  
  return 0;
}
