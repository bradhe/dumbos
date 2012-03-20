#include "video.h"

void kmain(void * mbd, unsigned int magic) {
  UNUSED(mbd);
  UNUSED(magic);

  char * str = "Hello, World!";

  int video_size = 80*26, i;
  v_char chars[80*26];

  for(i = 0; i < video_size; i++) {
    chars[i].value = 0x00;
    chars[i].color = 0x07;
  }

  for(i = 0; i < 13; i++) {
    chars[i].value = str[i];
  }

  video_show_buffer(chars, 80*26);
}

