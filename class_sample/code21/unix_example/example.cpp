#include <vector>
#include <iostream>
#include <cstdlib>

// unix stuff
#include <sys/types.h>
#include <unistd.h>

void child(int pfds[])
{
  std::vector<double> data = {3.141592, 6.0, 1.0/3, 0.000000001};

  std::cout << "Values written to the pipe." << std::endl;
  for(auto value : data){
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // write the size of the vector in binary format
  typedef std::vector<double>::size_type SizeType;
  SizeType len = data.size();
  write(pfds[1], reinterpret_cast<char*>(&len), sizeof(SizeType));

  // write each entry in binary format
  for(auto value : data){
    write(pfds[1], reinterpret_cast<char*>(&value), sizeof(double));
  }      
}

void parent(int pfds[])
{
  std::vector<double> data;
  char buf[256];
  
  // read the size of the vector in binary format from the pipe
  typedef std::vector<double>::size_type SizeType;
  SizeType len;
  read(pfds[0], reinterpret_cast<char*>(&len), sizeof(SizeType));
  data.resize(len);

  // read each entry in binary format
  for(SizeType i = 0; i < len; ++i){
    double value;
    read(pfds[0], reinterpret_cast<char*>(&value), sizeof(double));
    data[i] = value;
  }

  std::cout << data.size() << " values read from the pipe." << std::endl;
  for(auto value : data){
    std::cout << value << " ";
  }
  std::cout << std::endl;
}

int main()
{
  int pfds[2];
  char buf[100];

  // create a pipe to be shared between parent and child
  pipe(pfds);

  if (!fork()) {
    std::cout << "child process: writing to the pipe\n" << std::endl;
    child(pfds);
    std::cout << "child process exiting" << std::endl;
    exit(EXIT_SUCCESS);
  }
  else {
    std::cout << "parent process reading from pipe\n" << std::endl;
    parent(pfds);
    wait(0);
  }

  return EXIT_SUCCESS;
}
