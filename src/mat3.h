/*
	mat3.h 
*/
#ifndef __MAT3_H
#define __MAT3_H

#include "vec2.h"

typedef struct _Mat3
{
	float m00, m01, m02;
	float m10, m11, m12;
	float m20, m21, m22;
} Mat3;

extern Mat3* mat3_create();
extern void mat3_destroy(Mat3 *m);
extern void mat3_set_identity(Mat3 *m);
extern void mat3_set_scale(Mat3 *m, float s);
extern void mat3_set_translate(Mat3 *m, float tx, float ty);
extern void mat3_copy(Mat3 *ma, Mat3 *mb);
extern void mat3_set_rotate(Mat3 *m, float angle);
extern void mat3_add(Mat3 *ma, Mat3 *mb);
extern void mat3_sub(Mat3 *ma, Mat3 *mb);
extern void mat3_multiply(Mat3 *ma, Mat3 *mb);
extern void mat3_transform(Mat3 *m, Vec2 *v, float vz);
extern void mat3_invert(Mat3 *m);

#endif // __MAT3_H
