/*
 * dj_primitives.h
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 */

#ifndef DJ_PRIMITIVES_H_
#define DJ_PRIMITIVES_H_


void drawFace(dj_face f);
void drawFaces(dj_face *f, int count, int texture_id);
void drawMesh(mesh m);

void drawSquare(double xa, double ya, int texture_id);
void drawWall(facing_t dir, double length, double height, int texture_id);

#endif /* DJ_PRIMITIVES_H_ */
