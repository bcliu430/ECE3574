// simulate an event loop as continually prompting for strings
// the strings are treated as events. Use callbacks to handle them.

#include <iostream>
#include <string>

#include "callback_library.h"

// a function as a callback
void handle1(EventType e) {
  std::cout << "handle1 function, handling event " << e << std::endl;
}

// a different function as a callback
void handle2(EventType e) {
  std::cout << "handle2 function, handling event " << e << std::endl;
}

int main(int argc, char *argv[]) {
  std::string prompt = "> ";
  std::string input;

  // the MainObject instance
  MainObject mainobj;

  // setup callbacks for specific events
  mainobj.addHandler(std::string("event1"), handle1);
  mainobj.addHandler(std::string("event2"), handle2);

  // simulate an event loop
  while (true) {

    // simulate an event
    std::cout << prompt;
    std::cin >> input;

    // respond to the event
    mainobj.handleEvent(input);
  }

  return 0;
}
