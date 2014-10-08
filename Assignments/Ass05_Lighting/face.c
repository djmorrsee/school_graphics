#include "face.h"

void replaceFace(face* f, vert *a, vert *b, vert *c)
{
	float ux, uy, uz, vx, vy, vz;

	// Normals
	ux = a->x - b->x;
	uy = a->y - b->y;
	uz = a->z - b->z;

	vx = c->x - b->x;
	vy = c->y - b->y;
	vz = c->z - b->z;

	// Replace
	f->a = a;
	f->b = b;
	f->c = c;

	f->nx = uy * vz - uz * vy;
	f->ny = uz * vx - ux * vz;
	f->nz = ux * vy - uy * vx;
}

face* newFace (vert *a, vert *b, vert *c)
{
	face f;
	replaceFace(&f, a, b, c);
	return &f;
}
