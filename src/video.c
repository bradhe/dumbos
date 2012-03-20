#include "video.h"

BOOL video_create_buffer(v_char ** b) {
  /* All we need to do is allocate a buncha memory for this thing */
  UNUSED(b);
  return TRUE;
}

void video_show_buffer(v_char * buf, COUNTER size) {
  BYTE * videoram = (BYTE *) 0xb8000;
  COUNTER i;

  for(i = 0; i < size; i++) {
    v_char p = buf[i];	

    videoram[0] = p.value;
    videoram[1] = p.color;

    /* Also, need next video slot */
    videoram += 2;
  }
}

