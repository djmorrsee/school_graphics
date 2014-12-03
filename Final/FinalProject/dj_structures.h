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

typedef struct {
	double x;
	double y;
	double z;
} vector3;

typedef struct {

	double x;
	double y;
	double z;
	double a;

} vector4;

typedef struct {
	vector3 position;
	vector2 tex_coords;
} dj_vert;

dj_vert new_vert (double _x, double _y, double _z, double tx, double ty);
dj_vert norm_dj_vert (dj_vert v);
vector3 norm_vert (vector3 v);

typedef struct {
	dj_vert a;
	dj_vert b;
	dj_vert c;

	double norm_x;
	double norm_y;
	double norm_z;

} dj_face;

dj_face new_face (dj_vert _a, dj_vert _b, dj_vert c);

typedef struct {
	dj_face faces[1024];
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

light new_light (float *rgb, float *spec, float *amb, float *pos);

#endif /* DJ_STRUCTURES_H_ */
