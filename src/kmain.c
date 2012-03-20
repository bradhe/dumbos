#include "mm.h"

void kmain(void * mbd, unsigned int magic) {
  UNUSED(mbd);
  UNUSED(magic);

  do_e820();
}

