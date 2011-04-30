#ifndef _VIDEO_H
#define _VIDEO_H

typedef struct {
	unsigned char value;
	unsigned char color; 
} v_char;

int video_create_buffer(v_char **);
void video_show_buffer(v_char *, unsigned int);

#endif
