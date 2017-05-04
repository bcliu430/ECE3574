#include <iostream>
#include <thread>
#include <chrono>
#include <random>

#include "message_queue.h"

typedef int Message;
typedef message_queue<Message> MessageQueue;

// for generating random sleep times
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> unif(1, 2500);

class Consumer
{
public:

  Consumer(MessageQueue *messageQueuePtr, int identifier)
  {
    mq = messageQueuePtr;
    id = identifier;
  }
  
  void operator()() const
  {
    for(int i = 0; i < 10; ++i){
      Message m;
      mq->wait_and_pop(m);
      int work_time = unif(gen);
      std::cout << "Consumer " << id << " has taken product " << m
		<< " will work for " << work_time << " ms." 
		<< std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(work_time));
    }
  }

private:

  int id;
  MessageQueue * mq;
};

class Producer
{
public:

  Producer(MessageQueue *messageQueuePtr)
  {
    mq = messageQueuePtr;
  }
  
  void operator()() const
  {
    for(int i = 0; i < 10; ++i){
      mq->push(i);

      std::cout << "Producer has added product " << i
		<< std::endl;
      int work_time = unif(gen);
      std::this_thread::sleep_for(std::chrono::milliseconds(work_time));
    }
  }

private:
  MessageQueue * mq;
};

int main()
{
  MessageQueue mq;

  std::cout << "Starting producers and consumers." << std::endl;

  Consumer c1(&mq, 1);
  std::thread consumer_th1(c1);

  Producer p1(&mq);
  std::thread producer_th1(p1);
  
  consumer_th1.join();
  producer_th1.join();

  return 0;
}
