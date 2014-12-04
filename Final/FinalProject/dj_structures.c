/*
 * 
 */
#include "dj.h"

vector2 norm_vector2 (vector2 v)
{
	float len = sqrt(v.x * v.x + v.y * v.y);
	vector2 nv = { .x = v.x / len, .y = v.y / len };
	return nv;
}

vector3 norm_vector3 (vector3 v)
{
	float len = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	vector3 nv = { .x = v.x / len, .y = v.y / len, .z = v.z / len };
	return nv;
}

vector4 norm_vector4 (vector4 v)
{
	float len = sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.a*v.a);
	vector4 nv = { .x = v.x / len, .y = v.y / len, .z = v.z / len, .a=v.a/len };
	return nv;
}

vert new_vert (double _x, double _y, double _z, double tx, double ty)
{
	vert vert = { .position.x = _x, .position.y = _y, .position.z = _z, .tex_coord.x = tx, .tex_coord.y = ty };
	return vert;
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

face new_face (vert _a, vert _b, vert _c)
{
	vector3 normals = norm_vector3(cross_product(_a.position, _b.position));

	face face = { .a = _a, .b = _b, .c = _c, .normal.x = normals.x, .normal.y = normals.y, .normal.z = normals.z};
	return face;
}


light new_light (vector3 pos)
{
	light l = 	{ 
				.diffuse.x = 1,
				.diffuse.y = 0,
				.diffuse.z = 1,
				.diffuse.a = 1,
				
				.specular.x = 1,
				.specular.y = 1,
				.specular.z = 1,
				.specular.a = 1,
				 
				.ambient.x = .1,
				.ambient.y = .1,
				.ambient.z = .1,
				.ambient.a = 1,
				
				.position.x = pos.x,
				.position.y = pos.y,
				.position.z = pos.z
				};
	return l;
}
