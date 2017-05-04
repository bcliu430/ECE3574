// This implementation defines the possible actor types in the controller
// but this could be better done using a member template
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "actor_id.h"
#include "message.h"

// we want the controller central so
// we make it a Singleton

class ControllerImpl; // forward declare implementation

class Controller
{
public:
  
  Controller(Controller const&) = delete;            
  void operator=(Controller const&) = delete; 

  // singleton instance
  static Controller& getInstance(){
    static Controller instance;
    return instance;
  }

  enum ActorType {A,B};

  ActorIDType spawn(ActorType type);

  void send(ActorIDType receiver, Message message);
  
  void exit(ActorIDType identifier);

  void wait_for_actors();
  
  ~Controller();
    
private:
  Controller(); // hide
  
  ControllerImpl * pimpl;
};


#endif // _CONTROLLER_H_
