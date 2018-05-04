/* 
	graphic.h
*/
#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include "image.h"
#include "mat3.h"

extern void set_video_mode(unsigned char mode);
extern void init_graphics();
extern void clear_screen();
extern void set_pixel(int x, int y, unsigned char color);
extern void draw_image(Image *image, int sx, int sy);
extern void draw_transf_image(Image *image, int sx, int sy, Mat3 *transf);
extern Image* create_rectangle_image(int width, int height, unsigned char color);
extern void show();
extern void load_palette(char *filename);

#endif // __GRAPHIC_H