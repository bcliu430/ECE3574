#include "Vector.h"

#include <algorithm>
#include <stdexcept>

template <typename T>
VectorIterator<T>::VectorIterator(Vector<T> * that)
{
  vec = that;
  ptr = vec->data;
}
  
template <typename T>
T & VectorIterator<T>::get()
{
  return *ptr;
}

template <typename T>
void VectorIterator<T>::next()
{
  if( !isAtEnd() ) ++ptr;
}

template <typename T>
bool VectorIterator<T>::isAtEnd()
{
  return (ptr == (vec->data + vec->len));
}


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

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin()
{
  return Vector<T>::Iterator(this);
}
