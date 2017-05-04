#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>

template <typename T>
class ThreadSafeVector:private std::vector<T>{
public:
  ThreadSafeVector(){};

  ThreadSafeVector(std::size_t reserve):std::std::vector<T>::reserve(size){};

  T get (std::size_t index){
      std::lock_guard<std::mutex> guard(veclock);
      return at(index);
  }

  void T set (std::size_t index, const T &value){
    std::lock_guard<std::mutex> guard(veclock);
    this ->[index] = value;
  }

private:
  mutable std::mutex veclock;
};

#endif
