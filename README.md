# Welcome to DumbOS

This is a very simple toy OS. It doesn't really do much.

## Building DumbOS

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
