#include "video.h"

int video_create_buffer(v_char ** b) {
	/* All we need to do is allocate a buncha memory for this thing */
	return 0;
}

void video_show_buffer(v_char * buf, unsigned int size) {
	unsigned char * videoram = (unsigned char *) 0xb8000;
	int i;

	for(i = 0; i < size; i++) {
		v_char p = buf[i];	

		videoram[0] = p.value;
		videoram[1] = p.color;
	
		/* Also, need next video slot */
		videoram += 2;
	}
}
