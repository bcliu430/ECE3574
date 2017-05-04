#ifndef POLYMORPHIC_LIBRARY_H
#define POLYMORPHIC_LIBRARY_H

#include <unordered_map>
#include <string>

// treat events as just strings, but these could be any object
typedef std::string EventType;

class Base{
public:

  virtual void handle(EventType e);
  
};
  
class MainObject{
public:

  void addHandler(EventType e, Base * handler);

  bool handleEvent(EventType e);

private:

  std::unordered_map<EventType, Base *> eventmap;
};


#endif
