#include "vert.h"

void replaceVert(vert* v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

vert* newVert(float x, float y, float z) {
	vert v;
	replaceVert(&v, x, y, z);
	return &v;
}
