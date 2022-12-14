//
#pragma once

//
#define ALIGN  32

//
#define MD5_H_SIZE     16 //Size in bytes - 128bits
#define SHA1_H_SIZE    20 //Size in bytes - 160bits
#define SHA224_H_SIZE  28 //Size in bytes - 224bits
#define SHA256_H_SIZE  32 //Size in bytes - 256bits
#define SHA512_H_SIZE  64 //Size in bytes - 512bits

//
#define break16(f, d, s)				\
  {							\
    *(d)       = f(s +  0);				\
    *(d + 1)   = f(s +  4);				\
    *(d + 2)   = f(s +  8);				\
    *(d + 3)   = f(s + 12);				\
    *(d + 4)   = f(s + 16);				\
    *(d + 5)   = f(s + 20);				\
    *(d + 6)   = f(s + 24);				\
    *(d + 7)   = f(s + 28);				\
    *(d + 8)   = f(s + 32);				\
    *(d + 9)   = f(s + 36);				\
    *(d + 10)  = f(s + 40);				\
    *(d + 11)  = f(s + 44);				\
    *(d + 12)  = f(s + 48);				\
    *(d + 13)  = f(s + 52);				\
    *(d + 14)  = f(s + 56);				\
    *(d + 15)  = f(s + 60);				\
  }

//
#define break16_64(f, d, s)				\
  {							\
    *(d)       = f(s +   0);				\
    *(d + 1)   = f(s +   8);				\
    *(d + 2)   = f(s +  16);				\
    *(d + 3)   = f(s +  24);				\
    *(d + 4)   = f(s +  32);				\
    *(d + 5)   = f(s +  40);				\
    *(d + 6)   = f(s +  48);				\
    *(d + 7)   = f(s +  56);				\
    *(d + 8)   = f(s +  64);				\
    *(d + 9)   = f(s +  72);				\
    *(d + 10)  = f(s +  80);				\
    *(d + 11)  = f(s +  88);				\
    *(d + 12)  = f(s +  96);				\
    *(d + 13)  = f(s + 104);				\
    *(d + 14)  = f(s + 112);				\
    *(d + 15)  = f(s + 120);				\
  }

//Works with u_int for whatever value for s - bit left rotation
#define lrot(v, s) ((v << s) | (v >> ((sizeof(u_int) * 8) - s)))

//Works with u_int for whatever value for s - bit left rotation
#define rrot(v, s) ((v >> s) | (v << ((sizeof(u_int) * 8) - s)))

//Works with u_int64 for whatever value for s - bit left rotation
#define lrot64(v, s) ((v << s) | (v >> ((sizeof(u_int64) * 8) - s)))

//Works with u_int64 for whatever value for s - bit left rotation
#define rrot64(v, s) ((v >> s) | (v << ((sizeof(u_int64) * 8) - s)))

//
typedef unsigned u_int;
typedef unsigned char byte;
typedef unsigned long long u_int64;
typedef unsigned __int128 u_int128;

//
void printhash(const byte *restrict hash, const u_int size);

//Big-endian for SHA & Little-endian for MD5
extern u_int byte2u_int_le(const byte *restrict b);
extern u_int byte2u_int_be(const byte *restrict b);
extern u_int64 byte2u_int64_be(byte *restrict b);
extern void u_int2byte_le(const u_int u, byte *restrict b);
extern void u_int2byte_be(const u_int u, byte *restrict b);
extern void u_int642byte_be(const u_int64 u, byte *restrict b);
extern void u_int1282byte_be(const u_int128 u, byte *restrict b);
