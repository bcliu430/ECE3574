#ifndef CALLBACK_LIBRARY_H
#define CALLBACK_LIBRARY_H

#include <string>
#include <unordered_map>
#include <functional>

// treat events as just strings, but these could be any object
typedef std::string EventType;

// treat callbacks as functions that take the event as an argument.
typedef std::function<void(EventType e)> CallbackType;
  
// this would typically be defined in a library
class MainObject{
public:

  void addHandler(EventType e, const CallbackType &cb);

  bool handleEvent(EventType e);

private:

  std::unordered_map<EventType, CallbackType> eventmap;
};


#endif
