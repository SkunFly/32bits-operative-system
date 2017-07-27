/*
---Programmable Interval Timer (PIT)---
- Chip connected to IRQ0
- Can interrupt the CPU at a user-defined rate (between 18.2Hz and 1.1931 MHz)
- Can implement system clock and multitasking
- Uses an internal clock (1.1931MHz) that uses a frequency divider.
- The PIT chip uses the following I/O ports:
  I/O port     Usage
  0x40         Channel 0 data port (read/write)
  0x41         Channel 1 data port (read/write)
  0x42         Channel 2 data port (read/write)
  0x43         Mode/Command register (write only, a read is ignored)

  We want to set the PIT up so it interrupts us at regular intervals, at
  frequency f.
  To do this, we use a 'divisor'.
*/

#include "timer.h"
#include "port.h"
#include "isr.h"
#include "../drivers/screen.h"
#include "../libc/function.h"

u32 tick = 0;

static void timer_callback(registers_t regs){
  tick++;
  UNUSED(regs);
}

void init_timer(u32 freq){
  // Register the timer callback (handler)
  register_interrupt_handler(IRQ0, &timer_callback);

  // The value we send to the PIT is the value to divide it's input clock
  // (1193180 Hz) by, to get our required frequency. Important to note is
  // that the divisor must be small enough to fit into 16-bits.
  u32 divisor = 1193180 / freq;

  u8 low  = (u8)(divisor & 0xFF);
  u8 high = (u8)( (divisor >> 8) & 0xFF);

  // Send the command
  port_byte_out(0x43, 0x36); /* Command register port */
  port_byte_out(0x40, low);
  port_byte_out(0x40, high);
}
