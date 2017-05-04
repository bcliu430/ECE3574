#include "controller.h"

#include "controller_impl.h"

Controller::Controller()
{
  pimpl = new ControllerImpl;
}

ActorIDType Controller::spawn(ActorType type)
{
  return pimpl->spawn(type);
}

void Controller::send(ActorIDType receiver, Message message)
{
  pimpl->send(receiver, message);
}

void Controller::exit(ActorIDType identifier)
{
  pimpl->exit(identifier);
}

void Controller::wait_for_actors()
{
  pimpl->wait_for_actors();
}

Controller::~Controller(){
  delete pimpl;
}
