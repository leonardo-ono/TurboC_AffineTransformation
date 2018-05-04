/*
	vec2.c 
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vec2.h"

Vec2* vec2_create(float x, float y)
{
	Vec2 *vec2 = malloc(sizeof(Vec2));
	if (vec2 == NULL)
	{
		printf("could not allocate memory for Vec2 !\n");
		exit(-1);
	}
	vec2->x = x;
	vec2->y = y;
	return vec2;
}

void vec2_destroy(Vec2 *v)
{
	free(v);
}

void vec2_set(Vec2 *v, float x, float y)
{
	v->x = x;	
	v->y = y;	
}

void vec2_add(Vec2 *va, Vec2 *vb)
{
	va->x += vb->x;	
	va->y += vb->y;	
}

void vec2_sub(Vec2 *va, Vec2 *vb)
{
	va->x += vb->x;	
	va->y += vb->y;	
}

void vec2_scale(Vec2 *v, float s)
{
	v->x *= s;	
	v->y *= s;	
}

float vec2_dot(Vec2 *va, Vec2 *vb)
{
	return va->x * vb->x + va->y * vb->y;	
}

float vec2_cross(Vec2 *va, Vec2 *vb)
{
	return va->x * vb->y - vb->x * va->y;	
}

float vec2_get_length(Vec2 *v)
{
	return sqrt(v->x * v->x + v->y * v->y);
}

void vec2_normalize(Vec2 *v)
{
	float length = vec2_get_length(v);
	if (length != 0)
	{
		vec2_scale(v, 1 / length);
	}	
}
