
#ifndef _CONTROLLER_IMPL_H_
#define _CONTROLLER_IMPL_H_

#include <thread>
#include <mutex>
#include <vector>
#include <map>

#include "message_queue.h"

#include "controller.h"
#include "actor_base.h"

// controller implementation
// needs to be thread-safe
class ControllerImpl
{
public:

  ControllerImpl();
  
  ActorIDType spawn(Controller::ActorType type);

  void send(ActorIDType receiver, Message message);
  
  void exit(ActorIDType identifier);

  void wait_for_actors();
    
private:

  // factory for actors
  ActorBase * New(Controller::ActorType type);
    
  // a mutex to protect singleton access
  std::mutex the_mutex;

  // last used actor id, todo: overflow?
  ActorIDType last_id_used;

  // collection of actor objects
  std::map<ActorIDType, ActorBase *> actors;
  
  // the mailboxes
  std::map<ActorIDType, MailboxType> mailboxes;
  
  // the thread pool
  std::map<ActorIDType, std::thread> pool;

  // queue of actors to be deleted
  MessageQueue<ActorIDType> delete_queue;
  
};

#endif // _CONTROLLER_IMPL_H_
