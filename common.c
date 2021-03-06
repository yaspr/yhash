#include <stdio.h>
#include "common.h"

//
void printhash(const byte *restrict hash, const u_int size)
{
  for (int i = 0; i < size; i++)
    printf("%2.2x", hash[i]);
  
  printf("\n");
}

//Convert a u_int into 4 bytes - no implicit casting ! (little-endian)
void u_int2byte_le(const u_int u, byte *restrict b)
{
  b[3] = u >> 24;
  b[2] = u >> 16;
  b[1] = u >>  8;
  b[0] = u;
}

//Converts 4 bytes into a u_int - no implicit casting ! (little-endian)
u_int byte2u_int_le(const byte *restrict b)
{
  register u_int tmp = b[3];
  
  tmp = (tmp << 8) | b[2];
  tmp = (tmp << 8) | b[1];
  tmp = (tmp << 8) | b[0];
  
  return tmp;
}

//Convert u_int into 4 bytes (big-endian)
void u_int2byte_be(const u_int u, byte *restrict b)
{
  b[3] = u;
  b[2] = u >> 8;
  b[1] = u >> 16;
  b[0] = u >> 24;
} 

//Convert 4 bytes into a u_int (big-endian) 
u_int byte2u_int_be(const byte *restrict b)
{
  register u_int tmp = b[0];
  
  tmp = (tmp << 8) | b[1];
  tmp = (tmp << 8) | b[2];
  tmp = (tmp << 8) | b[3];
  
  return tmp;
}

//Convert u_int64 into 8 bytes (big-endian)
void u_int642byte_be(const u_int64 u, byte *restrict b)
{
  b[7] = u;
  b[6] = u >> 8;
  b[5] = u >> 16;
  b[4] = u >> 24;
  b[3] = u >> 32;
  b[2] = u >> 40;
  b[1] = u >> 48;
  b[0] = u >> 56;
} 

//Convert 8 bytes to u_int64 (big-endian)
u_int64 byte2u_int64_be(byte *restrict b)
{
  register u_int64 tmp = b[0];
  
  tmp = (tmp << 8) | b[1];
  tmp = (tmp << 8) | b[2];
  tmp = (tmp << 8) | b[3];
  tmp = (tmp << 8) | b[4];
  tmp = (tmp << 8) | b[5];
  tmp = (tmp << 8) | b[6];
  tmp = (tmp << 8) | b[7];
  
  return tmp;
} 

//Convert u_int128 into 16 bytes (big-endian)
void u_int1282byte_be(const u_int128 u, byte *restrict b)
{
  b[15] = u;
  b[14] = u >>   8;
  b[13] = u >>  16;
  b[12] = u >>  24;
  b[11] = u >>  32;
  b[10] = u >>  40;
  b[ 9] = u >>  48;
  b[ 8] = u >>  56;
  b[ 7] = u >>  64;
  b[ 6] = u >>  72;
  b[ 5] = u >>  80;
  b[ 4] = u >>  88;
  b[ 3] = u >>  96;
  b[ 2] = u >> 104;
  b[ 1] = u >> 112;
  b[ 0] = u >> 120;
} 
