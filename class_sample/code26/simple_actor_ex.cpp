#include <iostream>

#include "controller.h"
#include "actor_base.h"

int main()
{
  Controller::getInstance().spawn(Controller::ActorType::A);

  Controller::getInstance().wait_for_actors();
  
  return 0;
}
