#ifndef __DJ_FACE
#define __DJ_FACE

#include "vert.h"

typedef struct
{
	vert a;
	vert b;
	vert c;

	float nx;
	float ny;
	float nz;

} face;

void replaceFace(face* f, vert a, vert b, vert c);

void printFace(face f);

#endif
