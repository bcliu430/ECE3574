#include "polymorphic_library.h"

#include <iostream>

void Base::handle(EventType e){

  std::cout << "Default Handler on event " << e << std::endl;
}


void MainObject::addHandler(EventType e, Base * handler){
  eventmap[e] = handler; // note this replaces the old one if it exists
}

bool MainObject::handleEvent(EventType e){

    // lookup the event, if found call it and return true
    auto found = eventmap.find(e);
    if(found != eventmap.end()){
      found->second->handle(e);
      return true;
    }

    // no handler
    return false;
};
