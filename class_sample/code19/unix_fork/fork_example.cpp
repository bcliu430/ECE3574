#include <iostream>
#include <cstdlib>

// unix stuff
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
  // fork this process
  // return child pid if this is the parent process
  // otherwise return 0 if I am a child process
  pid_t child_pid = fork();

  if(-1 == child_pid){
    std::cerr << "Error: bad fork\n" << std::endl;
    exit(EXIT_FAILURE);
  }

  if(0 == child_pid){
    std::cout << "This code is running in the child process" << std::endl;
    std::cout << "My (child) pid is " << getpid() << std::endl;
    std::cout << "My parents pid is " << getppid() << std::endl;
    std::cout << "I (the child) will exit with success now." << std::endl;
    exit(EXIT_SUCCESS);
  }
  else{
    std::cout << "This code is running in the parent process" << std::endl;
    std::cout << "My (parent) pid is " << getpid() << std::endl;
    std::cout << "My child's pid is " << child_pid << std::endl;
    std::cout << "I will wait for my child to exit." << std::endl;
    int child_return_value;
    wait(&child_return_value);
    std::cout << "My child exited with return value " << child_return_value << std::endl;
    std::cout << "I (the parent) will exit with success now." << std::endl;
  }

  exit(EXIT_SUCCESS);
}
