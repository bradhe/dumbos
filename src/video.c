#include "video.h"

/**
 * Allocates a new buffer for manipulating video stuff.
 *
 * @param buf {v_char **} Where to stick the buffer.
 * @return {BOOL} True if successful, false otherwise.
 */
BOOL video_create_buffer(v_char ** b) {
  /* All we need to do is allocate a buncha memory for this thing */
  UNUSED(b);
  return TRUE;
}

/**
 * Copy the video buffer in to BIOS frame buffer.
 *
 * @param buf {v_char *} A buffer of characters to copy.
 * @param size {COUNTER} The number of characters to copy.
 */
void video_show_buffer(v_char * buf, COUNTER size) {
  BYTE * videoram = (BYTE *) VIDEO_PRIVATE_PARTS;
  COUNTER i;

  for(i = 0; i < size; i++) {
    v_char p = buf[i];	

    videoram[0] = p.value;
    videoram[1] = p.color;

    /* Also, need next video slot */
    videoram += 2;
  }
}
