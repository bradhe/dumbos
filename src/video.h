#ifndef _VIDEO_H
#define _VIDEO_H

#include "types.h"

#define VIDEO_PRIVATE_PARTS 0xb8000

typedef struct {
	BYTE value;
	BYTE color;
} v_char;

BOOL video_create_buffer(v_char **);
void video_show_buffer(v_char *, COUNTER);

#endif
