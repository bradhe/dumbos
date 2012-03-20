#include "video.h"

void kmain(void * mbd, unsigned int magic) {
  int video_size = 80*26, i;
  v_char chars[80*26];

  UNUSED(mbd);

  if(magic != 0x2badb002) {
    unsigned char * videoram = (unsigned char *) 0xb8000;
    videoram[0] = 66;
    videoram[1] = 0x07;
  }

  /*char * boot_loader_name = (char*) ((long*)mbd)[16];*/

  /*unsigned char * videoram = (unsigned char *) 0xb8000;*/
  for(i = 0; i < video_size; i++) {
    chars[i].value = 0;
    chars[i].color = 0;
  }

  video_show_buffer(chars, 80*26);
}

