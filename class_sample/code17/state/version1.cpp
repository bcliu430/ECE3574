#include <cassert>
#include <string>
#include <deque>
#include <iostream>
#include <sstream>

class Parser
{
public:
  enum VALUE {PASS, STORE, FINAL};

  Parser();
  void chomp(char c);
  std::string get();
  
private:

  static const char OPENTAG = '*';
  static const char CLOSETAG = '*';

  VALUE state;

  std::deque<char> buffer;
  std::string output;
};

Parser::Parser()
{
  state = Parser::PASS;
}

void Parser::chomp(char c)
{
  // next state logic
  if(state == Parser::PASS && c != OPENTAG){
    state = Parser::PASS;
  }
  else if(state == Parser::PASS && c == OPENTAG){
    state = Parser::STORE;
    return;
  }
  else if(state == Parser::STORE && c != CLOSETAG){
    state = Parser::STORE;
  }
  else if(state == Parser::STORE && c == CLOSETAG){
    state = Parser::FINAL;
  }
  else if(state == Parser::FINAL){
    state = Parser::PASS;
  }
  else{
    assert(false && "logic error");
  }

  // output logic
  if(state == Parser::PASS){
    output.push_back(c);
  }
  if(state == Parser::STORE){
    buffer.push_back(c);
  }
  if(state == Parser::FINAL){
    std::string temp(buffer.begin(), buffer.end());
    std::ostringstream oss;
    oss << output << "<i>" << temp << "</i>";
    output = oss.str();
  }
}

std::string Parser::get()
{
  return output;
}

int main()
{
  std::string input = "Hello *name*. How are you?";

  Parser fsm;
  for(auto it: input){
    fsm.chomp(it);
  }

  std::string output = fsm.get();
  std::cout << output << std::endl;
  
  return 0;
}
