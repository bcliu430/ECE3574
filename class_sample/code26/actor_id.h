// A simple unsigned int as the unique actor identifier
// this might not work well in a distributed system
// and would suffer from overflow in a large or long-running system
//
// An improvement would be to use a unique universal identifier (UUID)  
//
#ifndef _ACTOR_ID_H_
#define _ACTOR_ID_H_

typedef unsigned int ActorIDType;

#endif // _ACTOR_ID_H_
