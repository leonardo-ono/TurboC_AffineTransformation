/*
	vec2.h
*/
#ifndef __VEC2_H
#define __VEC2_H 

typedef struct _Vec2
{
	float x;
	float y;
} Vec2;

extern Vec2* vec2_create(float x, float y);
extern void vec2_destroy(Vec2 *v);
extern void vec2_set(Vec2 *v, float x, float y);
extern void vec2_add(Vec2 *va, Vec2 *vb);
extern void vec2_sub(Vec2 *va, Vec2 *vb);
extern void vec2_scale(Vec2 *v, float s);
extern float vec2_dot(Vec2 *va, Vec2 *vb);
extern float vec2_cross(Vec2 *va, Vec2 *vb);
extern float vec2_get_length(Vec2 *v);
extern void vec2_normalize(Vec2 *v);

#endif // __VEC2_H
