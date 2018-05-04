/*
	transf.c 
*/
#include "mat3.h"

static Mat3 tmp_transf;
static Mat3 *transf;

void transf_set(Mat3 *m)
{
	transf = m;
}

Mat3* transf_get()
{
	return transf;
}

void transf_set_identity()
{
	mat3_set_identity(transf);
}

void transf_scale(float s)
{
	mat3_set_scale(&tmp_transf, s);
	mat3_multiply(transf, &tmp_transf);
}

void transf_rotate(float angle)
{
	mat3_set_rotate(&tmp_transf, angle);
	mat3_multiply(transf, &tmp_transf);
}

void transf_translate(float tx, float ty)
{
	mat3_set_translate(&tmp_transf, tx, ty);
	mat3_multiply(transf, &tmp_transf);
}

