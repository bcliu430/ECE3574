#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
  int pfds[2];
  char buf[30];

  if (pipe(pfds) == -1) {
    exit(EXIT_FAILURE);
  }

  printf("Writing to pipe with file descriptor #%d\n", pfds[1]);
  write(pfds[1], "This is a test", 15);
  printf("Reading from pipe with file descriptor #%d\n", pfds[0]);
  read(pfds[0], buf, 30);
  printf("Read \"%s\" from the pipe\n", buf);

  return 0;
}
