#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct Task
{
  std::string description;
  bool completed;
  char priority;
  std::string context;
};

std::ostream& operator<<(std::ostream& os, const Task& task)
{
  const char delim = '|'; // what do you do if | is in the text?

  os << task.description << delim;
  os << task.completed << delim;
  os << task.priority << delim;
  os << task.context << std::endl;
  return os;
}

// this code can be tedious but can be reused easily
// there are many libraries that will do this
std::istream& operator>>(std::istream& is, Task& task)
{
  const char delim = '|'; // what do you do if | is in the text?

  // extract the line
  std::string line;
  std::getline(is, line);

  // extract description
  std::string description;
  std::stringstream desc_stream(line);
  std::getline(desc_stream, description, '|');
  task.description = description;
  
  // extract completed flag
  std::string complete_str;
  std::stringstream comp_stream(line);
  std::getline(comp_stream, complete_str, '|');
  // what is the string is "  0  "?
  task.completed = (complete_str == "0") ? false : true;

  // etc etc.

  return is;
}

int main()
{
  Task t1;
  t1.description = "do something";
  t1.completed = false;
  t1.priority = 'A';
  t1.context = "at work";

  // write to stdout
  std::cout << t1;

  // write to a file
  std::ofstream outfile("todo.txt");
  if(outfile.good()){
    outfile << t1;
  }
  outfile.close();

  // now read from the file
  std::ifstream infile("todo.txt");
  if(infile.good()){
    infile >> t1;
  }
  infile.close();
  
  return 0;
}
