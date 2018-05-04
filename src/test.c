#include <stdio.h> 
#include <math.h>

#include "mat3.h"
#include "transf.h"
#include "graphic.h"
#include "image.h"

void main()
{
	float angle = 0, scale = 1, oix, oiy;
	/* Image *image = create_rectangle_image(40, 40, 2); */
	Image *image = image_load("test.img");

	int i; 
	Mat3 *transf = mat3_create();

	set_video_mode(0x13);

	load_palette("test.pal");

	init_graphics();

	transf_set(transf);

	while (1)
	{
		float s = sin(angle * 0.5);
		float c = cos(angle * 0.5);

		oix = 160 + 100 * c;
		oiy = 100 + 50 * s;

		clear_screen();

		transf_set_identity();
		transf_translate(oix, oiy);
		transf_scale(scale);
		transf_rotate(-angle);
		transf_translate(-32, -32);
		draw_transf_image(image, 0, 0, transf);

		show();

		angle += 0.1;
		scale = 1.0 + 0.3 * fabs(sin(angle * 2));
		
		if (kbhit())
		{
			getch();
			set_video_mode(0x3);
			exit(1);
		}		
	}
}
