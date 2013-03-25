#include "types.h"
#include "mem.h"

#define MEM_MAX_PHYS_SLABS   16

typedef struct {
  void * base_addr;
  unsigned long size;
  unsigned long in_use;
} memory_slab_t;

typedef struct {
  unsigned long size;
  unsigned char type;

  // Points to the next reservation in the current slab. If null, this is the
  // last reservation in the slab.
  struct memory_reservation_t * next;
} memory_reservation_t;

static memory_slab_t memory_map[MEM_MAX_PHYS_SLABS];

void mem_clear_map() {
  for(int i = 0; i < MEM_MAX_PHYS_SLABS; i++) {
    memory_map[i].base_addr = (void *)(unsigned int)0;
    memory_map[i].size = 0;
  }
}

void mem_init(multiboot_memory_map_t * mmap, unsigned int mmap_len) {
  // We'll iterate using this.
  multiboot_memory_map_t *current = mmap;

  // Tracks how many we found.
  int count = 0;

  mem_clear_map();

  while(current < mmap + mmap_len) {
    current = (multiboot_memory_map_t*) ((unsigned int)current + current->size + sizeof(unsigned int));

    if(current->type != MULTIBOOT_MEMORY_AVAILABLE) {
      continue;
    }
    else {
      int idx = count++;

      kprintf("Found addressable memory. (%d) %l bytes\n", idx, current->len);
      memory_map[idx].base_addr = (void *)(unsigned long)current->addr;
      memory_map[idx].size      = (unsigned long)current->len;
      memory_map[idx].in_use    = 0;
    }
  }

  // Initialize a free reservation at the front of each slab to indicate it's
  // ready for bidness.
}

void * mem_alloc(unsigned long size) {
  // Find the first available slab and we'll go from there.
  for(int i = 0; i < MEM_MAX_PHYS_SLABS; i++) {
    memory_slab_t * seg = &memory_map[i];

    // If this is not allocated...
    if(seg->base_addr == 0) continue;
    if((seg->size - seg->in_use) >= size) {
      unsigned long offset = seg->in_use;
      seg->in_use += size;
      return seg->base_addr + offset;
    }
  }

  // If we got here, we couldn't find anything to allocate!
  return NULL;
}
