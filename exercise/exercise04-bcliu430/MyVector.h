///////////////////////////////////////////////////////////////////////////////
// filename:    MyVector.h
// name:        Beichen Liu
// Description: This header file is a c++ template that is used to create a
//              Vector(MyVector) and manipulate some cases on it.
// Version:     01-26-2017: created and wrote the template;
//
//
#include <vector>
#include <cstddef>
#include <stdexcept>

using namespace std;

template <typename T>
class MyVector{
public:
    MyVector();
    MyVector(const MyVector<T>& RHS);
    MyVector<T> &operator=(const MyVector<T>& RHS);
    ~MyVector();
    size_t size() const;
    bool empty() const;
    void push_back(const T& element);
    T& at(size_t pos);
    const T& at(size_t pos) const;

private:
  size_t __size;
  size_t capacity;

  T* data;
};


template<typename T>
MyVector<T>::MyVector():capacity(0),__size(0), data(nullptr){}

template<typename T>
MyVector<T>::MyVector(const MyVector<T>& RHS){ //RHS right hand side
    capacity = RHS.capacity;
    __size = RHS.__size;
    data = nullptr;

    if (capacity > 0) // size
        data = new T[capacity];

    for( uint32_t i = 0; i < __size; i++)
        data[i] = RHS.data[i]; // copy
}

template<typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector <T>& RHS){
    if ( this == & RHS)
         return *this;

    capacity = 0;
    __size = 0;
    delete []data;

    capacity = RHS.capacity;
    __size = RHS.__size;
    data = nullptr;

    if (capacity > 0)
        data = new T[capacity];

    for( uint32_t i = 0; i < __size; i++)
        data[i] = RHS.data[i]; // copy

    return *this;

}

template <typename T>
    MyVector<T>::~MyVector(){
        delete [] data;
    }


template <typename T>
    size_t MyVector<T>::size() const{
        return __size;
    }

template <typename T>
    bool MyVector<T>::empty() const{
     return(__size == 0);
    }


template <typename T>
void MyVector<T>::push_back(const T &element){
    if(__size +1 > capacity){
        if (capacity == 0)
            capacity = 1;
        else
            capacity += capacity;

        T* newData = new T[capacity];

        for( size_t i = 0; i < __size; i++)
            newData[i] = data[i];

        delete [] data;
        data = newData;
    }
    data[__size] = element;
    __size++;
}

template <typename T>
T & MyVector<T>::at(size_t pos) {
    if (pos >= __size)
         throw range_error("invalid position in at");
    return data [pos];
}

template <typename T>
const T & MyVector<T>::at(size_t pos) const{
    if (pos >= __size)
         throw range_error("invalid position in at");
    return data [pos];
}
