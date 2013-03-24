#include "types.h"
#include "mem.h"
#include "multiboot.h"

void kmain(multiboot_info_t * mbi, unsigned int magic) {
  UNUSED(magic);

  cls();
  mem_init((multiboot_memory_map_t*)mbi->mmap_addr, mbi->mmap_length);
  char * str = (char *)mem_alloc(sizeof(char)*13);

  if(str == NULL) {
    kprintf("Failed to allocate string.");
  } else {
    for(int i = 0; i < 13; i++) {
      str[i] = 0;
    }

    str[0]  = 'H';
    str[1]  = 'e';
    str[2]  = 'l';
    str[3]  = 'l';
    str[4]  = 'o';
    str[5]  = ',';
    str[6]  = ' ';
    str[7]  = 'W';
    str[8]  = 'o';
    str[9]  = 'r';
    str[10] = 'l';
    str[11] = 'd';
    str[12] = '\0';

    kprintf("Got message %s\n", str);
  }
}

