#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <string>

class Directory
{
public:
  Directory(const std::string & name);
  
  bool make();
  
private:
  std::string dirname;
};

#endif // _DIRECTORY_H_
