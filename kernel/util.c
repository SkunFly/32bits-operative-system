#include "util.h"

/* Copy bytes from one place to another */
void memory_copy(char* source, char* dest, int n_bytes){
  int i;
  for(i = 0; i < n_bytes; i++)
    *(dest + i) = *(source + i);
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

/* K&R */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R */
int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

unsigned short low_16(unsigned long n){ return n & 0xFFFF; }

unsigned short high_16(unsigned long n){ return (n >> 16) & 0xFFFF; }
