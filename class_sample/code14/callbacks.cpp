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


// define an example callback
void mycallback(int x){
  std::cout << "mycallback " << x << std::endl;
}

int main(int argc, char *argv[])
{

  Foo myfoo;
  myfoo.set_callback(mycallback);

  for(int i = -2; i <= 2; ++i){
    myfoo.set(i);
  }
  
  return 0;
}
