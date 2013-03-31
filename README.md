# Welcome to DumbOS

This is a very simple toy OS. It doesn't really do much.

## Tools

### C99 instead of ANSI C

Why? Because it's 2013. That's why.

### GCC 4.6

Why? Because it's the only thing I could figure out to build with...:) I would
prefer clang, frankly, but building bare C without stdlib in clang for ELF
instead of Mach on Mac seems/is hard.

## Getting Started

### Toolchain

Run `scripts/create_toolchain.sh` to install a fresh cross compiling toolchain targetting `i586-elf`. Includes the following:

* binutils 2.22
* GCC 4.6.3

### Building the OS

Use the following rake commands to make it go. Listed in order of dependency.

* `rake clean` cleans.
* `rake build` actually builds all source
* `rake floppy` generates a disk image
* `rake run` starts QEmu.

### Running

Use `rake run` to build the fucker and boot QEmu up. Then, once in grub, use the following:

```
kernel 200+18
boot
```
