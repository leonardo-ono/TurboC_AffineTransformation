/*
	transf.h 
*/

extern void transf_set(Mat3 *m);
extern Mat3* transf_get();
extern void transf_set_identity();
extern void transf_scale(float s);
extern void transf_rotate(float angle);
extern void transf_translate(float tx, float ty);
