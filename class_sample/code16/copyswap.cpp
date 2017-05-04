#include <algorithm>
#include <stdexcept>

// I have simlified Vector here to make the point clearer
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
  // we change the argument, see below
  Vector& operator=(Vector x);
  
  // we add a swap method
  void swap(Vector& a, Vector& b);
  
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
Vector<T>::Vector(const Vector<T> & x)
{
  length = x.length;
  data = length ? new T[length] : nullptr;
  std::copy(x.data, x.data + x.length, data);
}

template <typename T>
Vector<T>::~Vector()
{
  delete [] data;
}

// we simplify the copy assignment
// note the argument is now passed by value, not ref
// let the compiler make the copy
// this will not throw 
template <typename T>
Vector<T>& Vector<T>::operator=(Vector x)
{
  swap(*this, x);
  
  return *this;
}


// we implement the swap, can this ever throw an exception?
template <typename T>
void Vector<T>::swap(Vector<T>& a, Vector<T>& b)
{
  std::swap(a.length, b.length);
  std::swap(a.data, b.data);
}

int main()
{
  Vector<double> v;

  Vector<double> v2 = v;

  Vector<double> v3;
  v3 = v;
  
  return 0;
}
