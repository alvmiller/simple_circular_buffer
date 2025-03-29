#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

// https://en.wikipedia.org/wiki/Circular_buffer

enum { N = 10 };

int buffer [N];
int writeIndx = 0;
int readIndx  = 0;

int put (int item) 
{
  if ((writeIndx + 1) % N == readIndx) {
     return 0;
  }
  
  buffer[writeIndx] = item;
  writeIndx = (writeIndx + 1) % N;
  return 1;
}

int get (int * value) 
{
  if (readIndx == writeIndx) {
     return 0;
  }

  *value = buffer[readIndx];
  readIndx = (readIndx + 1) % N;
  return 1;
}

int main ()
{
  int value = 1001;
  while (put(value++));
  while (get(&value))
     printf ("read %d\n", value);
  return 0;
}
