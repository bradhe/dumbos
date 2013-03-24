#include "types.h"
#include "mem.h"

void mem_init(multiboot_memory_map_t * mmap, unsigned int mmap_len) {
  multiboot_memory_map_t *current = mmap;
  int count = 0;

  while(current < mmap + mmap_len) {
    current = (multiboot_memory_map_t*) ((unsigned int)current + current->size + sizeof(unsigned int));

    kprintf("Entry #%d\n", count);
    kprintf("addr: %d\n", current->addr);
    kprintf("size: %d\n", current->size);
    kprintf("type: %d\n", current->type);

    count++;
  }
}
