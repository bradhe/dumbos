#CARGS=-Wall -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs
CARGS=-nostdlib -nostartfiles -nodefaultlibs
CSRC=src/kmain.c src/video.c
SSRC=src/loader.s
KERNEL_OBJ=obj/kernel.o
LOADER_OBJ=obj/loader.o

all: clean ssrc csrc 
	ld -T src/linker.ld -o bin/kernel.bin $(LOADER_OBJ) $(KERNEL_OBJ)

clean:
	rm -rf bin
	rm -rf obj/*.o
	mkdir bin

floppy: all
	scripts/generate_postpad.sh
	cat lib/grub-0.97-i386-pc/boot/grub/stage1 lib/grub-0.97-i386-pc/boot/grub/stage2 lib/prepad bin/kernel.bin lib/postpad > bin/floppy.img

csrc:
	gcc -o $(KERNEL_OBJ) $(CSRC) $(CARGS)

ssrc:
	nasm -f elf -o $(LOADER_OBJ) $(SSRC)