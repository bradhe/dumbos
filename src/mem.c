#include "types.h"
#include "mem.h"

#define MEM_MAX_PHYS_SLABS   16

typedef struct {
  // Indicates the size of the reservation.
  unsigned long size;

  // Indicates the type of the reservation.
  unsigned char type;

  // Points to the next reservation in the current slab. If null, this is the
  // last reservation in the slab.
  struct memory_reservation_t * next;
} memory_reservation_t;

#define MEMORY_RESERVATION_FREE         0x01
#define MEMORY_RESERVATION_KERNEL       0x02
#define MEMORY_RESERVATION_USER         0x03

typedef struct {
  void * base_addr;
  unsigned long size;
  unsigned long in_use;
} memory_slab_t;

#define SLAB_ROOT(x)                    (memory_reservation_t *)x->base_addr

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

      memory_map[idx].base_addr = (void *)(unsigned long)current->addr;
      memory_map[idx].size      = (unsigned long)current->len;
      memory_map[idx].in_use    = 0;

      // Initialize a free reservation at the front of each slab to indicate it's
      // ready for bidness.
      memory_reservation_t * res = SLAB_ROOT((&memory_map[idx]));
      res->type = MEMORY_RESERVATION_FREE;
      res->size = memory_map[idx].size - sizeof(memory_reservation_t);
      res->next = NULL; // Always null to start.
    }
  }
}

BOOL mem_is_in_use(memory_reservation_t * res) {
  return AS_BOOL(res->type == MEMORY_RESERVATION_FREE);
}

void * mem_bisect_reservation(memory_reservation_t * res, unsigned long size) {
  // Don't do anything if there is not enough room.
  if(res->size < size) return NULL;

  // Change this reservation type, then at the end of this reservation we
  // create a new reservation record, which will be the next reservation.
  memory_reservation_t * prev = (memory_reservation_t *)res->next;

  // This is the start of the next record.
  memory_reservation_t * next = res + sizeof(memory_reservation_t) + size;
  next->type = MEMORY_RESERVATION_FREE;
  next->size = res->size - size - sizeof(memory_reservation_t);

  // Update the original record's size so that we're ready to go...
  res->size = size;

  // Preserve pointer to next reservation if there was/is one.
  next->next = (struct memory_reservation_t *)prev;

  // And mark it as in use...
  res->type = MEMORY_RESERVATION_KERNEL;

  return(res + sizeof(memory_reservation_t));
}

// Allocates a new memory reservation.
//
// @param size the size of the reservation.
// @return the address of the reservation, NULL if none can be made.
//
void * mem_alloc(unsigned long size) {
  // Find the first available slab and we'll go from there.
  for(int i = 0; i < MEM_MAX_PHYS_SLABS; i++) {
    memory_slab_t * seg = &memory_map[i];

    // If this is not allocated...
    if(seg->base_addr == 0) continue;

    memory_reservation_t * res = SLAB_ROOT(seg);

    // Find a free reservation that is in the right range.
    while(NOT_NULL(res)) {
      // If it's in use we will keep lookin'
      if(!mem_is_in_use(res)) continue;

      if(res->size >= size) {
        // We found a free reservation! Create a new reservation at the end of
        // this, and bisect the existing reservation.
        return mem_bisect_reservation(res, size);
      }

      // And we're off.
      res = (memory_reservation_t *)res->next;
    }
  }

  // If we got here, we couldn't find anything to allocate!
  return NULL;
}
