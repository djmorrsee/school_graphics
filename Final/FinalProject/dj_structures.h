/*
 * dj_structures.h
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 */

#ifndef DJ_STRUCTURES_H_
#define DJ_STRUCTURES_H_

typedef struct {
	double x;
	double y;
} vector2;
vector2 norm_vector2 (vector2 v);

typedef struct {
	double x;
	double y;
	double z;
} vector3;
vector3 norm_vector3 (vector3 v);

typedef struct {
	double x;
	double y;
	double z;
	double a;
} vector4;
vector4 norm_vector4 (vector4 v);

typedef struct {
	vector3 position;
	vector2 tex_coord;
} vert;

vert new_vert (double _x, double _y, double _z, double tx, double ty);

typedef struct {
	vert a;
	vert b;
	vert c;

	vector3 normal;

} face;

face new_face (vert _a, vert _b, vert c);

typedef struct {
	face faces[1024];
	int face_count;
	int texture_id;
} mesh;


// Lighting
typedef struct {
	vector4 diffuse;
	vector4 specular;
	vector4 ambient;
	vector3 position;

} light;

light new_light (vector3 pos);

#endif /* DJ_STRUCTURES_H_ */
