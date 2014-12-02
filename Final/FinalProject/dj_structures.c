/*
 * 
 */
#include "dj.h"

dj_vert new_vert (double _x, double _y, double _z, double tx, double ty)
{
	dj_vert vert = { .x = _x, .y = _y, .z = _z, .tex_x = tx, .tex_y = ty };
	return vert;
}


dj_vert cross_product(dj_vert a, dj_vert b)
{
	double nx = (a.y * b.z) - (a.z * b.y);
	double ny = (a.z * b.x) - (a.x * b.z);
	double nz = (a.x * b.y) - (a.y * b.x);

	// Get rid of -0s
	nx = nx ? nx : 0;
	ny = ny ? ny : 0;
	nz = nz ? nz : 0;

	return new_vert(nx, ny, nz, 0, 0);
}

dj_face new_face (dj_vert _a, dj_vert _b, dj_vert _c)
{
	dj_vert normals = cross_product(_a, _b);

	dj_face face = { .a = _a, .b = _b, .c = _c, .norm_x = normals.x, .norm_y = normals.y, .norm_z = normals.z};
	return face;
}


light new_light (float r, float g, float b, float x, float y, float z)
{
	light l = { .diffuse[0] = r, .diffuse[1] = g, .diffuse[2] = b, .position[0] = x, .position[1] = y, .position[2] = z};
	return l;
}
