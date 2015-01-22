#ifndef __DJ_PRIMITIVES
#define __DJ_PRIMITIVES

#include "vert.h"
#include "face.h"



void drawFace(face f);

// Method to draw a 1x1 square centered at 0, 0, 0 and facing towards the camera
void drawSquare();

void drawBox(float l, float w, float h);

void drawRoom(float l, float w, float h);

void drawCircle(float r, int v) ;

void drawCylinderBody(float r, float h, int v);

void drawCylinder(float r, float h, int v);

void drawIcosphere(int dim);

#endif
