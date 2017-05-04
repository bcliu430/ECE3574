#include "Directory.h"

#include <cstdlib>

int main(int argc, char * argv[])
{
  if(argc == 2)
    {
      Directory dir(argv[1]);
      bool err = dir.make();

      if(err) return EXIT_FAILURE;
      else return EXIT_SUCCESS;
    }

  return EXIT_FAILURE;
}
