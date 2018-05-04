/*
	graphic.c
*/

#include <stdlib.h>
#include <stdio.h> 
#include <dos.h>
#include <float.h>

#include "vec2.h"
#include "mat3.h"
#include "graphic.h"

unsigned char *VGA = (unsigned char *) 0xa0000000;
unsigned char *OFFSCREEN;

void set_video_mode(unsigned char mode)
{
	union REGS regs;
	regs.h.ah = 0;
	regs.h.al = mode;
	int86(0x10, &regs, &regs);
}

void init_graphics()
{
	OFFSCREEN = malloc(320 * 200);
}

void clear_screen()
{
	memset(OFFSCREEN, 127, 64000);
}

void set_pixel(int x, int y, unsigned char color)
{
	if (x < 0 || y < 0 || x > 319 || y > 199)
	{
		return;
	}
	OFFSCREEN[y * 320 + x] = color;
}

void draw_image(Image *image, int sx, int sy)
{
	int x, y;
	unsigned char color;
	for (y = 0; y < image->height; y++)
	{
		for (x = 0; x < image->width; x++)
		{
			color = image->data[y * image->width + x];
			set_pixel(x + sx, y + sy, color);
		}
	}
}

void draw_transf_image(Image *image, int tx, int ty, Mat3 *transf)
{
	Mat3 invert_transform;
	Vec2 vertices[4], tp;
	float min_x = FLT_MAX, min_y = FLT_MAX, max_x = FLT_MIN, max_y = FLT_MIN;
	unsigned int i, x, y, ix, iy;
	unsigned char color;

	vec2_set(&vertices[0], tx, ty);
	vec2_set(&vertices[1], tx + image->width, ty);
	vec2_set(&vertices[2], tx + image->width, ty + image->height);
	vec2_set(&vertices[3], tx, ty + image->height);

	mat3_transform(transf, &vertices[0], 1);
	mat3_transform(transf, &vertices[1], 1);
	mat3_transform(transf, &vertices[2], 1);
	mat3_transform(transf, &vertices[3], 1);

	for (i = 0; i < 4; i++)
	{
		if (vertices[i].x < min_x)
		{
			min_x = vertices[i].x;
		}
		if (vertices[i].x > max_x)
		{
			max_x = vertices[i].x;
		}
		if (vertices[i].y < min_y)
		{
			min_y = vertices[i].y;
		}
		if (vertices[i].y > max_y)
		{
			max_y = vertices[i].y;
		}
	}

	mat3_copy(&invert_transform, transf);
	mat3_invert(&invert_transform);

	if (min_x < 0)
	{
		min_x = 0;
	}
	if (max_x > 319)
	{
		max_x = 319;
	}
	if (min_y < 0)
	{
		min_y = 0;
	}
	if (max_y > 199)
	{
		max_y = 199;
	}

	for (y = min_y; y <= max_y; y++)
	{
		for (x = min_x; x <= max_x; x++)
		{
			vec2_set(&tp, x, y);
			mat3_transform(&invert_transform, &tp, 1);
			if (tp.x < 0 || tp.y < 0 || tp.x > image->width || tp.y > image->height)
			{
				continue;
			}
			ix = (int) tp.x;
			iy = (int) tp.y;
			color = image->data[iy * image->width + ix];

			if (color != 0)
			{
				/* set_pixel(x, y, color); */
				OFFSCREEN[y * 320 + x] = color;
			}
		}
	}
	
	/*
	for (i = 0; i < 4; i++)
	{
		set_pixel(vertices[i].x, vertices[i].y, 15);
	}
	*/
}

Image* create_rectangle_image(int width, int height, unsigned char color)
{
	int i, x, y, image_size = width * height;
	Image *image = malloc(sizeof(Image));
	if (image == NULL)
	{
		printf("could not allocate memory for image !");
		exit(-1);
	}
	image->data = malloc(image_size);
	if (image->data == NULL)
	{
		printf("could not allocate memory for image !");
		exit(-1);
	}
	image->width = width;
	image->height = height;
	
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			image->data[y * image->width + x] = x / 4 + y / 4 + color;
		}
	}
	
	/* memset(image->data, color, image_size); */
	
	return image;
}

void show()
{
	memcpy(VGA, OFFSCREEN, 64000);
}

void load_palette(char *filename)
{
	FILE *file_handler;
	unsigned char c[768];
	unsigned int i;
	
	file_handler = fopen(filename, "rb");
	for (i = 0; i < 768; i++)
	{
		c[i] = fgetc(file_handler);
	}
	fclose(file_handler);
	
	outp(0x03c8, 0);
	for (i = 0; i < 768; i += 3)
	{
		unsigned char r = (unsigned char) c[i] >> 2;
		unsigned char g = (unsigned char) c[i + 1] >> 2;
		unsigned char b = (unsigned char) c[i + 2] >> 2;
		outp(0x03c9, r);
		outp(0x03c9, g);
		outp(0x03c9, b);
		/* printf("color %d -> %d %d %d\n", i / 3, r, g, b); */
	}
	
}