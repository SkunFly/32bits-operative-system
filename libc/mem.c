#include "mem.h"

/* Copy bytes from one place to another */
void memory_copy(char* source, char* dest, int n_bytes){
  int i;
  for(i = 0; i < n_bytes; i++)
    *(dest + i) = *(source + i);
}

/* Sets a value in a length of memory */
void memory_set(u8 *dest, u8 val, u32 len) {
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

unsigned short low_16(unsigned long n){ return n & 0xFFFF; }

unsigned short high_16(unsigned long n){ return (n >> 16) & 0xFFFF; }
