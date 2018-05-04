/*
	image.c
*/
#include <stdio.h> 
#include <alloc.h>
#include "image.h"

Image* image_load(char *filename)
{
	Image *image;
	FILE *file_handler;
	char c[5];
	unsigned int width, height, image_size, i;
	
	file_handler = fopen(filename, "rb");
	
	/* first get image size */
	fgets(c, 5, file_handler);
	width = *(unsigned int *) c;
	height = *(unsigned int *) (c + 2);
	image_size = width * height;
	
	image = (Image *) malloc(sizeof(Image));
	if (image == NULL)
	{
		printf("could not allocate memory for image !");
		exit(-1);
	}
	image->width = width;
	image->height = height;
	
	image->data = (unsigned char *) malloc(image_size + 1);
	if (image->data == NULL)
	{
		printf("could not allocate memory for image !");
		exit(-1);
	}
	
	/* fgets(image->data, image_size + 1, file_handler); */
	
	for (i = 0; i < image_size; i++)
	{
		unsigned char c = fgetc(file_handler);
		image->data[i] = c;
	}

	fclose(file_handler);
	return image;
}
