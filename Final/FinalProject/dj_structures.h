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
	double z;

	double tex_x;
	double tex_y;
} dj_vert;

dj_vert new_vert (double _x, double _y, double _z, double tx, double ty);
dj_vert norm_dj_vert (dj_vert v);
void norm_vert (float v[3]);

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
	double diffuse[4];
	double specular[4];
	double ambient[4];
	double position[3];
} light;

light new_light (float *rgb, float *spec, float *amb, float *pos);

#endif /* DJ_STRUCTURES_H_ */
