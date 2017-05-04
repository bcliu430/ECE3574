#include <iostream>
//#include <cstdio>
#include <cstdlib>

// unix stuff
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int pfds[2];
  char buf[100];

  // create a pipe to be shared between parent and child
  pipe(pfds);

  if (!fork()) {
    std::cout << "child process: writing to the pipe\n" << std::endl;
    write(pfds[1], "This is a message from child", 29);
    std::cout << "child process exiting" << std::endl;
    exit(EXIT_SUCCESS);
  }
  else {
    std::cout << "parent process reading from pipe" << std::endl;
    read(pfds[0], buf, 100);
    std::cout << "parent process read: " << buf << std::endl;
    wait(0);
  }

  return 0;
}
