#ifndef __DJ_VERT
#define __DJ_VERT

typedef struct
{
	float x;
	float y;
	float z;
} vert;

void replaceVert(vert* v, float x, float y, float z);

#endif
