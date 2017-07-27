#include "mem.h"
#include "../libc/string.h"
#include "../drivers/screen.h"

unsigned short low_16(unsigned long n){ return n & 0xFFFF; }

unsigned short high_16(unsigned long n){ return (n >> 16) & 0xFFFF; }

/* Copy bytes from one place to another */
void memory_copy(char* source, char* dest, int n_bytes){
  int i;
  for(i = 0; i < n_bytes; i++)
    *(dest + i) = *(source + i);
}

/* Sets a value in a length of memory */
void memory_set(uint8_t *dest, uint8_t val, uint32_t len) {
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

// Kernel starts at 0x1000
uint32_t free_mem_addr = 0x10000;

// TODO: fix (http://wiki.osdev.org/James_Molloy%27s_Tutorial_Known_Bugs#Problem:_kmalloc_isn.27t_properly_aligned)
uint32_t kmalloc(size_t size, int align, uint32_t *phys_addr) {
    char page_str[16] = "";
    hex_to_ascii(free_mem_addr, page_str);
    print(page_str);
    /* Pages are aligned to 4K, or 0x1000 */
    if (align == 1 && (free_mem_addr & 0xFFFFF000)) {
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    /* Save also the physical address */
    if (phys_addr) *phys_addr = free_mem_addr;

    uint32_t ret = free_mem_addr;
    free_mem_addr += size; /* Remember to increment the pointer */
    return ret;
}
