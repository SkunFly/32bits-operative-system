#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

void memory_copy(char* source, char* dest, int n_bytes);
void memory_set(u8 *dest, u8 val, u32 len);
unsigned short low_16(unsigned long n);
unsigned short high_16(unsigned long n);

#endif
