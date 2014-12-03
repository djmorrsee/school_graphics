/*
 * 
 */
#include "dj.h"

dj_vert new_vert (double _x, double _y, double _z, double tx, double ty)
{
	dj_vert vert = { .position.x = _x, .position.y = _y, .position.z = _z, .tex_coords.x = tx, .tex_coords.y = ty };
	return vert;
}

dj_vert norm_dj_vert (dj_vert v)
{
	float len = sqrt(v.position.x*v.position.x + v.position.y*v.position.y + v.position.z*v.position.z);
	return new_vert(v.position.x/len, v.position.y/len, v.position.z/len, v.tex_coords.x, v.tex_coords.y);
}

vector3 norm_vert (vector3 v)
{
	float len = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	vector3 nv = { .x = v.x / len, .y = v.y / len, .z = v.z / len };
	return nv;
}

vector3 cross_product(vector3 a, vector3 b)
{
	vector3 cross;

	cross.x = (a.y * b.z) - (a.z * b.y);
	cross.y = (a.z * b.x) - (a.x * b.z);
	cross.z = (a.x * b.y) - (a.y * b.x);

	cross.x = cross.x ? cross.x : 0;
	cross.y = cross.y ? cross.y : 0;
	cross.z = cross.z ? cross.z : 0;

	return cross;

}

dj_face new_face (dj_vert _a, dj_vert _b, dj_vert _c)
{
	vector3 normals = cross_product(_a.position, _b.position);

	dj_face face = { .a = _a, .b = _b, .c = _c, .norm_x = normals.x, .norm_y = normals.y, .norm_z = normals.z};
	return face;
}


light new_light (float *rgb, float *spec, float *amb, float *pos)
{
	light l = 	{ 
				.diffuse.x = rgb[0],
				.diffuse.y = rgb[1],
				.diffuse.z = rgb[2],
				.diffuse.a = rgb[3],
				
				.specular.x = spec[0],
				.specular.y = spec[1],
				.specular.z = spec[2],
				.specular.a = spec[3],
				 
				.ambient.x = amb[0],
				.ambient.y = amb[1],
				.ambient.z = amb[2],
				.ambient.a = amb[3],
				
				.position.x = pos[0],
				.position.y = pos[1],
				.position.z = pos[2]
				};
	return l;
}
