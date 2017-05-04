#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cstdlib>

// simple iterator wrapping a pointer

template <typename T> class Vector;

template <typename T>
class VectorIterator
{
public:
  T& get();
  void next();
  bool isAtEnd();
  
private:

  VectorIterator(Vector<T> * that);
  
  T* ptr;
  Vector<T> * vec;

  // give the other class accees to the private constructor
  friend class Vector<T>;
};

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

  // we add the following
  typedef VectorIterator<T> Iterator;
  Iterator begin();
  
private:

  T * data;
  std::size_t len;

  // give the iterator access
  friend class VectorIterator<T>;
};

#include "Vector.tpp"

#endif // _VECTOR_H_
