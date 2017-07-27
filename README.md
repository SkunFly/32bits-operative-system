# Synopsis
This repository is the result of my continuous process in learning the bases of the creation of an opetative system.
If you too are learning you can use this repository, most of the times i try to comment the code.

I also recommend you to use this links as reference:
* [OSDev.org](http://wiki.osdev.org/Main_Page)
* [JamesM's kernel development tutorials](https://web.archive.org/web/20160412174753/http://www.jamesmolloy.co.uk/tutorial_html/index.html)

# Running
Requierements:
* [x86 CrossCompiler](http://wiki.osdev.org/GCC_Cross-Compiler)
Use this path:
```
export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
```
* [Qemu](http://www.qemu.org/)

Once you have created the Cross Compiler and installed Qemu you can use the given Makefile
```
make run
```
# Features
This SO implements this features (this list is ordered by development):
- [x] Bootload
- [x] Enter 32-bit mode
- [x] Screen output
- [x] Screen scroll
- [x] Interrupt handling
- [x] Keyboard input (US keyboard - some scancodes are not yet implemented)
- [x] Simple Shell
- [ ] Memory Managment
- [ ] Multithreaded Kernel
- [ ] File System
- [ ] User space

# Todo List
- [ ] Fix kmalloc
- [ ] Implement Missing Functions (memset, memcpy, memmove and memcmp functions)
