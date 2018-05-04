/*
	image.h 
*/

#ifndef __IMAGE_H
#define __IMAGE_H

typedef struct _Image
{
	unsigned int width;
	unsigned int height;
	unsigned char *data;
} Image;

extern Image* image_load(char* filename);

#endif // __IMAGE_H