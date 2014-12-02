/*
 * 
 */
#include "dj.h"

dj_vert new_vert (double _x, double _y, double _z, double tx, double ty)
{
	dj_vert vert = { .x = _x, .y = _y, .z = _z, .tex_x = tx, .tex_y = ty };
	return vert;
}

dj_vert norm_dj_vert (dj_vert v)
{
	float len = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	return new_vert(v.x/len, v.y/len, v.z/len, v.tex_x, v.tex_y);
}

void norm_vert (float v[3])
{
	float len = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	v[0] = v[0] / len;
	v[1] = v[1] / len;
	v[2] = v[2] / len;
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


light new_light (float *rgb, float *spec, float *amb, float *pos)
{
	light l = 	{ 
				.diffuse[0] = rgb[0], 
				.diffuse[1] = rgb[1], 
				.diffuse[2] = rgb[2],
				.diffuse[3] = rgb[3],
				
				.specular[0] = spec[0], 
				.specular[1] = spec[1], 
				.specular[2] = spec[2],
				.specular[3] = spec[3],
				 
				.ambient[0] = amb[0], 
				.ambient[1] = amb[1], 
				.ambient[2] = amb[2],
				.ambient[3] = amb[3],
				
				.position[0] = pos[0], 
				.position[1] = pos[1], 
				.position[2] = pos[2]
				};
	return l;
}
