/*
 * dj_primitives.h
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 */

#ifndef DJ_PRIMITIVES_H_
#define DJ_PRIMITIVES_H_


void drawFace(face f);
void drawFaces(face *f, int count, int texture_id);
void drawMesh(mesh m);


void drawPlane(int res, int texture_id);
void drawSquare(double xa, double ya, int texture_id);
void drawWall(facing_t dir, double length, double height, int texture_id);

// Final Project Specific
void draw_structure();

#endif /* DJ_PRIMITIVES_H_ */
