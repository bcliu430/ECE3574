// Define some example actors:
// ActorA spawns ActorB and sends an integer message
// ActorB checks for a message that is positive
//        and spawns another ActorB sending it a one smaller integer message
//
// Other ideas: add timeouts for receive
//              add ability to monitor child actors
#ifndef _ACTORS_H_
#define _ACTORS_H_

#include <iostream>

class ActorA: public ActorBase
{
public:
  ActorA(ActorIDType identifier, MailboxType * mailbox)
    : ActorBase(identifier, mailbox){}
  
  void operator()() {
    std::cout << "Actor A, spawning ActorB" << std::endl;
    ActorIDType b_id = Controller::getInstance().spawn(Controller::ActorType::B);

    Message msg = 100;
    std::cout << "Actor A, sending message " << msg
	      << " to ActorB with id " << b_id << std::endl;
    Controller::getInstance().send(b_id, msg);
    
    ActorBase::exit(); // what if this is not the last thing it calls?
  }  
};

class ActorB: public ActorBase
{
public:
  ActorB(ActorIDType identifier, MailboxType * mailbox)
    : ActorBase(identifier, mailbox){}
  
  void operator()() {
      std::cout << "Actor B, waiting for messages" << std::endl;
      Message m = ActorBase::receive();
      std::cout << "Actor B, received " << m << std::endl;

      if(m > 0){
	std::cout << "Actor B, spawning ActorB" << std::endl;
	ActorIDType b_id = Controller::getInstance().spawn(Controller::ActorType::B);
	
	Message msg = m-1;
	std::cout << "Actor B with id " << getID()
		  << ", sending message " << msg
		  << " to ActorB with id " << b_id << std::endl;
	Controller::getInstance().send(b_id, msg);
      }
      
      ActorBase::exit(); // what if this is not the last thing it calls?
  }  
};


#endif // _ACTORS_H_
