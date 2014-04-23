#include <stdio.h>
#include <string.h>

#include "hash.h"

int main(int argc, char **argv)
{
  if (argc < 2)
    return printf("%s [STRING]\n", argv[0]), 0;
  
  u_int64 len = strlen(argv[1]);
  byte hash[MD5_H_SIZE] __attribute__((aligned(ALIGN)));
  
  md5hash(argv[1], strlen(argv[1]), hash);
  
  printhash(hash, MD5_H_SIZE);
  
  return 0;
}
