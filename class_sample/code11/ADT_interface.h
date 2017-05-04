
#ifndef _ABSTRACT_BAG_H_
#define _ABSTRACT_BAG_H_

template<typename T>
class AbstractBag
{
public:

  virtual bool add(const T& item) = 0;

  virtual bool remove(const T& item) = 0;

  virtual bool isEmpty() = 0;

  virtual int getCurrentSize() = 0;

  virtual bool contains(const T& item) = 0;

  virtual void clear() = 0;
};

template <typename T>
class ArrayBag: public AbstractBag<T>
{
public:
  
private:
  T data[100];
  std::size_t size;
};

template <typename T>
class LinkedBag: public AbstractBag<T>
{
public:

private:

  struct Node
  {
    Node * next;
    T data;
  };

  Node * head;
  std::size_t size;
}



#endif // _ABSTRACT_BAG_H_

