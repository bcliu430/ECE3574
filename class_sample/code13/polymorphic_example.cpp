// simulate an event loop as continually prompting for strings
// the strings are treated as events. Use virtual calls to handle them.

#include <string>
#include <iostream>

#include "polymorphic_library.h"

class Handle1: public Base{

public:

  void handle(EventType e){
    std::cout << "Handle1 handle of event " << e << std::endl;
  }

};

class Handle2: public Base{

public:

  Handle2(): count(0) {};
  
  void handle(EventType e){
    count += 1;
    std::cout << "Handle2 handle of event " << e << " "
	      << count << " times." << std::endl;
  }
  
private:
  int count;
};

int main(int argc, char *argv[])
{
  std::string prompt = "> ";
  std::string input;

  // the MainObject instance
  MainObject mainobj;

  // Handler objects
  Handle1 h1;
  Handle2 h2;
  
  // setup handlers for specific events
  mainobj.addHandler(std::string("event1"), &h1);
  mainobj.addHandler(std::string("event2"), &h2);

  // simulate an event loop
  while(true){

    // simulate an event
    std::cout << prompt;
    std::cin >> input;

    // respond to the event
    mainobj.handleEvent(input);
  }

  return 0;
}
