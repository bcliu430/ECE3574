#include <cassert>
#include <string>
#include <deque>
#include <iostream>
#include <sstream>

// base "idle" state
class State
{
public:
  void setInput(char c){
    input = c;
  }
  virtual State * next(){return this;};
  virtual void update(std::deque<char>& buffer,
		      std::string& output){};

protected:
  char input;

  static const char OPENTAG = '*';
  static const char CLOSETAG = '*';
};

class PassState: public State
{
  State * next();
  void update(std::deque<char>& buffer,
	      std::string& output);
};

class StoreState: public State
{
  State * next();
  void update(std::deque<char>& buffer,
	      std::string& output);
};

class FinalState: public State
{
  State * next();
  void update(std::deque<char>& buffer,
	      std::string& output);
};

State * PassState::next()
{
  if(input == OPENTAG){
    return new StoreState;
  }
  return this;
}

void PassState::update(std::deque<char>& buffer,
		       std::string& output)
{
  output.push_back(input);
}

State * StoreState::next()
{
  if(input == CLOSETAG){
    return new FinalState;
  }

  return this;
}

void StoreState::update(std::deque<char>& buffer,
			std::string& output)
{
  buffer.push_back(input);
}

State * FinalState::next()
{
  return new PassState;
}

void FinalState::update(std::deque<char>& buffer,
			std::string& output)
{
  std::string temp(buffer.begin(), buffer.end());
  std::ostringstream oss;
  oss << output << "<i>" << temp << "</i>";
  output = oss.str();
}

class Machine
{
public:
  Machine(){
    current = new PassState;
  }
  ~Machine(){
    delete current;
  }
  void update(char c){
    State * previous = current;
    current->setInput(c);
    State * next = current->next();
    if(next != current){
      delete current;
      current = next;
    }
    current->update(buffer, output);
  }

  std::string get(){return output;};
  
private:
  State * current;

  std::deque<char> buffer;
  std::string output;

};

int main()
{
  std::string input = "Hello *name*. How are you?";

  Machine fsm;
  for(auto it: input){
    fsm.update(it);
  }

  std::string output = fsm.get();
  std::cout << output << std::endl;
  
  return 0;
}
