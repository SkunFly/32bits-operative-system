#include "port.h"

unsigned char port_byte_in(unsigned short port){
  // "=a" (result) means: put AL register in variable RESULT when finished
  // "d" (port) means: load EDX with port
  unsigned char result;
  asm("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

void port_byte_out(unsigned short port, unsigned char data){
  asm("out %%al, %%dx" : :"a" (data) , "d" (port));
}

unsigned short port_word_in(unsigned short port){
  unsigned short result;
  asm("in %%dx, %%al" : "=a"(result) : "d"(port));
  return result;
}

void port_word_out(unsigned short port, unsigned short data){
  asm("out %%al, %%dx" : :"a" (data) , "d" (port));
}
