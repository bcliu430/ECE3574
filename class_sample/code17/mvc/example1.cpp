// a simple example
#include <cstdlib>
#include <iostream>
#include <vector>

// a generic list model
template <typename T>
struct ListModel
{
  virtual std::size_t length() = 0;
  virtual T get(std::size_t index) = 0;
};

// a generic list view
template <typename T>
class ListView
{
public:

  void show(){
    for(std::size_t i = 0; i < model->length(); ++i){
      std::cout << model->get(i) << " | ";
    }
    std::cout << std::endl;
  }

  void setModel(ListModel<T> * m){
    model = m;
  }
  
private:
  ListModel<T> * model;
};


// a templated class that conforms to the ListModel interface
// for demontration, just an adaptor of std::vector
// note: std::vector does not have methods named  get or length
template <typename T>
class SimpleList: public ListModel<T>, public std::vector<T>
{
public:
  std::size_t length(){
    return std::vector<T>::size();
  }
  T get(std::size_t index){
    return (*this)[index];
  }
};
  
int main()
{
  SimpleList<int> alist;

  alist.push_back(0);
  alist.push_back(1);
  alist.push_back(2);
  alist.push_back(3);
  
  ListView<int> view;

  view.setModel(&alist);

  view.show();
    
  return 0;
}
