#include "djgraphics.h"

vert newVert(float x, float y, float z, float tx, float ty)
{
	vert v;// = (vert*)malloc(sizeof(vert));
	v.x = x;
	v.y = y;
	v.z = z;
	
	v.tx = tx;
	v.ty = ty;
	return v;
}

float distance(vert a, vert b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + (a.z - b.z, 2));
}
