#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

// unix include neeeded
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
  assert(argc == 2);
  
  const char *name = "/count";	// key name
  const int SIZE = 256;	// shared memory size

  int shm_fd; // file descriptor, from shm_open()
  void * shm_base;  // base address, from mmap()

  // create the shared memory segment
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1) {
    std::cout << argv[1] << " shared memory failed!" << std::endl;
    exit(EXIT_FAILURE);
  }

  // size the memory segment
  ftruncate(shm_fd, SIZE);

  // map the shared memory segment to our address space
  shm_base = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (shm_base == MAP_FAILED) {
    std::cout << argv[1] << " mapping memory failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  // treat the shared memory as a std::size_t object
  std::size_t * counter = reinterpret_cast<std::size_t *>(shm_base);
  
  *counter = 0;
  while (true){
    std::cout << argv[1] << " Loop " << *counter << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ++(*counter);
    
    if(*counter > 10){
      std::cout << argv[1] << " Breaking because counter == " << *counter << std::endl;
      break;
    }
  }

  // remove the mapped memory segment from our address space
  if (munmap(shm_base, SIZE) == -1) {
    std::cout << argv[1] << " unmapping memory failed!" << std::endl;
    exit(EXIT_FAILURE);
  }

  // close the shared memory segment
  if (close(shm_fd) == -1) {
    std::cout << argv[1] << " closing failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
    
  return 0;
}
