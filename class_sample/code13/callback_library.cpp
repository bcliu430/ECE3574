#include "callback_library.h"

void MainObject::addHandler(EventType e, const CallbackType &cb){
  eventmap[e] = cb; // note this replaces the old one if it exists
}

bool MainObject::handleEvent(EventType e){

    // lookup the event, if found call it and return true
    auto found = eventmap.find(e);
    if(found != eventmap.end()){
      found->second(e);
      return true;
    }

    // no handler
    return false;
};
