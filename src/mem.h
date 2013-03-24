#ifndef _MEM_H
#define _MEM_H

#include "output.h"
#include "multiboot.h"

void mem_init(multiboot_memory_map_t*, unsigned int);
void * mem_alloc(unsigned long);

#endif
