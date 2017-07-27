#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stddef.h>

void memory_copy(char* source, char* dest, int n_bytes);
void memory_set(uint8_t *dest, uint8_t val, uint32_t len);
uint32_t kmalloc(uint32_t size, int align, uint32_t *phys_add);
unsigned short low_16(unsigned long n);
unsigned short high_16(unsigned long n);

#endif
