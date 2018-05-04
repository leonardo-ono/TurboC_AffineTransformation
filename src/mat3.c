/*
	mat3.c 
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vec2.h"
#include "mat3.h"

Mat3* mat3_create()
{
	Mat3 *mat3 = malloc(sizeof(Mat3));
	if (mat3 == NULL)
	{
		printf("could not allocate memory for Mat3 !\n");
		exit(-1);
	}
	return mat3;
}

void mat3_destroy(Mat3 *m)
{
	free(m);
}

void mat3_set_identity(Mat3 *m)
{
	m->m00 = 1;
	m->m01 = 0;
	m->m02 = 0;
	m->m10 = 0;
	m->m11 = 1;
	m->m12 = 0;
	m->m20 = 0;
	m->m21 = 0;
	m->m22 = 1;
}

void mat3_set_scale(Mat3 *m, float s)
{
	m->m00 = s;
	m->m01 = 0;
	m->m02 = 0;
	m->m10 = 0;
	m->m11 = s;
	m->m12 = 0;
	m->m20 = 0;
	m->m21 = 0;
	m->m22 = 1;
}

void mat3_set_rotate(Mat3 *m, float angle)
{
	float s = sin(angle);
	float c = cos(angle);
	m->m00 = c;
	m->m01 = -s;
	m->m02 = 0;
	m->m10 = s;
	m->m11 = c;
	m->m12 = 0;
	m->m20 = 0;
	m->m21 = 0;
	m->m22 = 1;
}

void mat3_set_translate(Mat3 *m, float tx, float ty)
{
	m->m00 = 1;
	m->m01 = 0;
	m->m02 = tx;
	m->m10 = 0;
	m->m11 = 1;
	m->m12 = ty;
	m->m20 = 0;
	m->m21 = 0;
	m->m22 = 1;
}

void mat3_copy(Mat3 *ma, Mat3 *mb)
{
	memcpy(ma, mb, sizeof(Mat3));
}

void mat3_add(Mat3 *ma, Mat3 *mb)
{
	ma->m00 += mb->m00;
	ma->m01 += mb->m01;
	ma->m02 += mb->m02;
	ma->m10 += mb->m10;
	ma->m11 += mb->m11;
	ma->m12 += mb->m12;
	ma->m20 += mb->m20;
	ma->m21 += mb->m21;
	ma->m22 += mb->m22;
}

void mat3_sub(Mat3 *ma, Mat3 *mb)
{
	ma->m00 -= mb->m00;
	ma->m01 -= mb->m01;
	ma->m02 -= mb->m02;
	ma->m10 -= mb->m10;
	ma->m11 -= mb->m11;
	ma->m12 -= mb->m12;
	ma->m20 -= mb->m20;
	ma->m21 -= mb->m21;
	ma->m22 -= mb->m22;
}

void mat3_multiply(Mat3 *ma, Mat3 *mb)
{
	float mn00 = ma->m00 * mb->m00 + ma->m01 * mb->m10 + ma->m02 * mb->m20;
	float mn01 = ma->m00 * mb->m01 + ma->m01 * mb->m11 + ma->m02 * mb->m21;
	float mn02 = ma->m00 * mb->m02 + ma->m01 * mb->m12 + ma->m02 * mb->m22;
	float mn10 = ma->m10 * mb->m00 + ma->m11 * mb->m10 + ma->m12 * mb->m20;
	float mn11 = ma->m10 * mb->m01 + ma->m11 * mb->m11 + ma->m12 * mb->m21;
	float mn12 = ma->m10 * mb->m02 + ma->m11 * mb->m12 + ma->m12 * mb->m22;
	float mn20 = ma->m20 * mb->m00 + ma->m21 * mb->m10 + ma->m22 * mb->m20;
	float mn21 = ma->m20 * mb->m01 + ma->m21 * mb->m11 + ma->m22 * mb->m21;
	float mn22 = ma->m20 * mb->m02 + ma->m21 * mb->m12 + ma->m22 * mb->m22;
	ma->m00 = mn00;
	ma->m01 = mn01;
	ma->m02 = mn02;
	ma->m10 = mn10;
	ma->m11 = mn11;
	ma->m12 = mn12;
	ma->m20 = mn20;
	ma->m21 = mn21;
	ma->m22 = mn22;
}

void mat3_transform(Mat3 *m, Vec2 *v, float vz)
{
	float nx = m->m00 * v->x + m->m01 * v->y + m->m02 * vz;
	float ny = m->m10 * v->x + m->m11 * v->y + m->m12 * vz;
	/* float nz = ma->m20 * v->x + ma->m21 * v->y + ma->m22 * v->z; */
	v->x = nx;
	v->y = ny;
	/* v->z = nz */
}

void mat3_invert(Mat3 *m)
{
	float detInv = 1 / (m->m00 * m->m11 - m->m01 * m->m10);
	
	/* TODO needs to check if not invertible ?*/
	
	float nm00 =  m->m11 * detInv;
	float nm10 = -m->m10 * detInv;
	float nm01 = -m->m01 * detInv;
	float nm11 =  m->m00 * detInv;
	float nm02 = (m->m01 * m->m12 - m->m11 * m->m02) * detInv;
	float nm12 = (m->m10 * m->m02 - m->m00 * m->m12) * detInv;        
	m->m00 = nm00;
	m->m01 = nm01;
	m->m02 = nm02;
	m->m10 = nm10;
	m->m11 = nm11;
	m->m12 = nm12;
	m->m20 = 0;
	m->m21 = 0;
	m->m22 = 1;
}

