#include "controller_impl.h"

#include <cassert>

#include "actors.h"

ControllerImpl::ControllerImpl(): last_id_used(0) {}
  
ActorIDType ControllerImpl::spawn(Controller::ActorType type)
{
  std::lock_guard<std::mutex> guard(the_mutex);
  
  ActorBase * actor = New(type);
  
  return actor->getID();
}

void ControllerImpl::send(ActorIDType receiver, Message message)
{
  std::lock_guard<std::mutex> guard(the_mutex);

  // get the mailbox assocaited with the receiver id
  std::map<ActorIDType, MailboxType>::iterator it = mailboxes.find(receiver);
  if(it != mailboxes.end()){ // if it is a valid id
    // push the message into it
    it->second.push(message);
  }
}

void ControllerImpl::exit(ActorIDType identifier)
{
  // schedule actor to be deleted
  delete_queue.push(identifier);

}

void ControllerImpl::wait_for_actors()
{
  std::unique_lock<std::mutex> this_lock(the_mutex, std::defer_lock);

  bool exit_flag = false;
  while(!exit_flag){
    // wait for next to delete
    ActorIDType id;
    delete_queue.wait_and_pop(id);
    
    // call join on the thread
    pool[id].join();

    // lock the controller
    this_lock.lock();

    // call actor destructor
    delete actors[id];
    
    // remove actor pointer from map
    actors.erase(id);

    // delete the mailbox
    mailboxes.erase(id);

    // delete the thread
    pool.erase(id);
    
    // if no more actors, get ready to exit
    if(actors.empty()) exit_flag = true;
      
    // unlock the controller
    this_lock.unlock();
  }
}


ActorBase * ControllerImpl::New(Controller::ActorType type)
{
  // create an id for the actor
  ++last_id_used;
  ActorIDType id = last_id_used;
  
  // create a mailbox for the actor 
  MailboxType& mb = mailboxes[id];
  
  switch(type)
    {
    case Controller::A:
      {
	ActorA * temp =  new ActorA(id, &mb);
	actors[id] = temp;
	pool.emplace(id, std::thread(*temp));
	
	return temp;
      }
    case Controller::B:
      {
	ActorB * temp =  new ActorB(id, &mb);
	actors[id] = temp;
	pool.emplace(id, std::thread(*temp));
	
	return temp;
      }
    default:
      assert(false && "Unknown Actor Type in Factory");
    }
}
