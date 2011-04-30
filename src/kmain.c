#include "video.h"

void kmain(void * mbd, unsigned int magic) {
	if(magic != 0x2badb002) {
		unsigned char * videoram = (unsigned char *) 0xb8000;
		videoram[0] = 66;
		videoram[1] = 0x07;
	}

	char * boot_loader_name = (char*) ((long*)mbd)[16];

	unsigned char * videoram = (unsigned char *) 0xb8000;
	v_char chars[80*26] = { 0, 0 };
	video_show_buffer(chars, 80*26);
}
