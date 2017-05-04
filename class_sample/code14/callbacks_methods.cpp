#include <functional>
#include <iostream>

typedef std::function<void(int)> CallbackType;

// An example class with a callback stored
class Foo{
public:

  void set_callback(CallbackType cb){
    callback = cb;
  }

  // this is just an example, this could be any change to the Foo object
  void set(int value){
    avalue = value;

    // call the callback
    callback(avalue); 
  }

private:

  CallbackType callback;
  int avalue;
};


// define an example callback as a member function (method)
class Handler{
public:

  Handler(): value(0){};
  
  void handle(int x){
    std::cout << "Handler::handle " << x << std::endl;
    value += x;
  }

  int sum(){
    return value;
  }
  
private:
  int value;
};

int main(int argc, char *argv[])
{

  Foo myfoo;
  Handler myhandler;

  // here we build a function by binding the class instance to its member function
  CallbackType f = std::bind(&Handler::handle, &myhandler, std::placeholders::_1);

  // now we set the callback as before
  myfoo.set_callback(f);

  for(int i = -2; i <= 2; ++i){
    myfoo.set(i);
  }

  std::cout << myhandler.sum() << std::endl;
  
  return 0;
}
