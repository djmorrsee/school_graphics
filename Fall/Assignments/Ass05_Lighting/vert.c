#include <math.h>
#include "vert.h"

void replaceVert(vert* v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

void normalize(vert *v) 
{
	float len = sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
	replaceVert(v, v->x / len, v->y / len, v->z / len);
}

float distance(vert a, vert b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + (a.z - b.z, 2));
}
