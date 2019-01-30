#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
  int pid;
  int k, nprocess;
  int z, steps;
  char buffer_src[1024], buffer_dst[1024];

  if (argc != 3) {
    printf(2, "usage: %s nsubprocess nsteps\n", argv[0]);
    exit();
  }

  nprocess = atoi(argv[1]);
  steps = atoi(argv[2]);

  for (k = 0; k < nprocess; k++) {
    pid = fork ();
    if (pid < 0) {
      printf(1, "%d failed in fork!\n", getpid());
      exit();
    } else if (pid == 0) {  
      // child
      printf(1, "[pid=%d] created\n", getpid());
      for (z = 0; z < steps; z += 1) {
         // copy buffers one inside the other and back
         // used for wasting cpu time
         memmove(buffer_dst, buffer_src, 1024);
         memmove(buffer_src, buffer_dst, 1024);
      }
      exit();
    }
  }

  for (k = 0; k < nprocess; k++) {
    pid = wait();
    printf(1, "[pid=%d] terminated\n", pid);
  }

  exit();
}
