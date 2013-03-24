#include "types.h"
#include "mem.h"
#include "multiboot.h"

void kmain(multiboot_info_t * mbi, unsigned int magic) {
  UNUSED(magic);

  cls();
  mem_init((multiboot_memory_map_t*)mbi->mmap_addr, mbi->mmap_length);

  while(1) {}
}

