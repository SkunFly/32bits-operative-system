#include "kernel.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

void main(){
  isr_install();
  irq_install();

  print("Type something, it will go through the kernel\n"
         "Type END to halt the CPU\n");
}


void shell(char* input){
  if(strcmp(input, "END") == 0){
    print("Stopping the CPU. Bye!\n");
    asm volatile("hlt");
  }
  print("$> ");
  print(input);
  print("\n");
}
