#include "Directory.h"

//*****************************************
#ifdef _OS_WINDOWS
#include <Windows.h>

bool mkdir_impl(const std::string & name)
{
  return CreateDirectory(name.c_str(), NULL);
}
#endif
//*****************************************

//*****************************************
#ifdef _OS_OSX

#include <sys/stat.h>

bool mkdir_impl(const std::string & name)
{
  const int err = mkdir(name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

  return (err != -1);
}
#endif
//*****************************************

//*****************************************
#ifdef _OS_LINUX
#include <sys/stat.h>

bool mkdir_impl(const std::string & name)
{
  const int err = mkdir(name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

  return (err != -1);
}
#endif
//*****************************************


Directory::Directory(const std::string & name): dirname(name)
{}

bool Directory::make()
{
  return mkdir_impl(dirname);
}

