#include <stdio.h>
#include "face.h"

void replaceFace(face* f, vert a, vert b, vert c)
{

	// Replace
	f->a = a;
	f->b = b;
	f->c = c;

	f->nx = -(b.y - a.y) * (c.z - a.z) + (c.y - a.y) * (b.z - a.z);
	f->ny = -(b.z - a.z) * (c.x - a.x) + (b.x - a.x) * (c.z - a.z);
	f->nz = -(b.x - a.x) * (c.y - a.y) + (c.x - a.x) * (b.y - a.y);
	
	if(f->nx == 0)
		f->nx = 0;
		
	if(f->ny == 0)
		f->ny = 0;
		
	if(f->nz == 0)
		f->nz = 0;

}

void printFace(face f) 
{
	printf("Face:: A(%.2f, %.2f, %.2f) B(%.2f %.2f %.2f) C(%.2f %.2f %.2f)\n", f.a.x, f.a.y, f.a.z, f.b.x, f.b.y, f.b.z, f.c.x, f.c.y, f.c.z);
}
