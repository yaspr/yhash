#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

//
const u_int sha256_k[64] __attribute__((aligned(ALIGN))) = { 0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 
							     0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
							     0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 
							     0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
							     0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 
							     0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
							     0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 
							     0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
							     0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 
							     0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
							     0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 
							     0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
							     0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 
							     0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
							     0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 
							     0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2 };

//
void sha256hash(const byte *restrict msg, const u_int64 len, byte *restrict hash)
{
  byte *newmsg = NULL;
  u_int64 newlen = len;
  u_int M[64] __attribute__((aligned(ALIGN))), A, B, C, D, E, F, G, H, temp1, temp2,
        a0 = 0x6A09E667, b0 = 0xBB67AE85, c0 = 0x3C6EF372, d0 = 0xA54FF53A, 
        e0 = 0x510E527F, f0 = 0x9B05688C, g0 = 0x1F83D9AB, h0 = 0x5BE0CD19;
 
  //Padding
  
  while ((++newlen & 63) != 56);
  
  newmsg = malloc(newlen + 8); //8 => u_int64 - Replace with aligned malloc 
  memcpy(newmsg, msg, len);    //Replace with fast memcpy
  
  *(newmsg + len) = 0x80; //Padding with '1' bit
  
  for (int i = len + 1; i < newlen; i++) //Padding with '0' bit
    *(newmsg + i) = 0x00;
  
  u_int642byte_be(len << 3, newmsg + newlen);
  
  //Hashing

  //64 ==> 512 bit blocks
  for (int block = 0; block < newlen; block += 64)
    {
      break16(byte2u_int_be, M, newmsg + block);
      
      //
      for (int i = 16; i < 64; i++)
	*(M + i) = *(M + i - 16) + (rrot(*(M + i - 15),  7) ^ rrot(*(M + i - 15), 18) ^ (*(M + i - 15) >>  3)) + 
	           *(M + i -  7) + (rrot(*(M + i -  2), 17) ^ rrot(*(M + i -  2), 19) ^ (*(M + i -  2) >> 10));
      
      A = a0, B = b0, C = c0, D = d0, E = e0, F = f0, G = g0, H = h0;
      
      for (int i = 0; i < 64; i++)
	{
	  temp1 = H + (rrot(E, 6) ^ rrot(E, 11) ^ rrot(E, 25)) + ((E & F) ^ ((~E) & G)) + *(sha256_k + i) + *(M + i);
	  temp2 = (rrot(A, 2) ^ rrot(A, 13) ^ rrot(A, 22)) + ((A & B) ^ (A & C) ^ (B & C));
	  
	  H = G;
	  G = F;
	  F = E;
	  E = D + temp1;
	  D = C;
	  C = B;
	  B = A;
	  A = temp1 + temp2;
	}
      
      a0 += A;
      b0 += B;
      c0 += C;
      d0 += D;
      e0 += E;
      f0 += F;
      g0 += G;
      h0 += H;
    }
  
  u_int2byte_be(a0, hash     );
  u_int2byte_be(b0, hash +  4);
  u_int2byte_be(c0, hash +  8);
  u_int2byte_be(d0, hash + 12);
  u_int2byte_be(e0, hash + 16);
  u_int2byte_be(f0, hash + 20);
  u_int2byte_be(g0, hash + 24);
  u_int2byte_be(h0, hash + 28);

  free(newmsg);
}
