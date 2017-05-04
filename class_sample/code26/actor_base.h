#ifndef _ACTOR_BASE_H_
#define _ACTOR_BASE_H_

#include "message_queue.h"

#include "actor_id.h"
#include "message.h"

// define the mailbox as out thread-safe message queue
typedef MessageQueue<Message> MailboxType;

// define a base class for Actors
// contruct with an identifier and a mailbox pointer
// overload operator() to define the actors behavior
//
// A posisble issue is that the actor might call exit but then never exit operator().
// How might this be prevented?
class ActorBase
{
public:

  ActorBase(ActorIDType identifier, MailboxType * mailbox)
    : id(identifier), mb(mailbox) {}

  virtual ~ActorBase(){}
  
  virtual void operator()() = 0;

  ActorIDType getID(){
    return id;
  }
  
protected:

  Message receive(){
    Message m;
    mb->wait_and_pop(m);
    return m;
  }
  
  void exit(){
    Controller::getInstance().exit(id);
  }

private:
  
  ActorIDType id;
  MailboxType * mb;
};


#endif // _ACTOR_BASE_H_
