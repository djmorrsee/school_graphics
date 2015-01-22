#ifndef __DJ_PRIMITIVES
#define __DJ_PRIMITIVES

#include "vert.h"

// Helper Method for Drawing a sequence of vertices.
// Verts contains all possible verts
// indices is a sequence of verts indexes that define faces.
void drawVerts(vert* verts, int* indices, int i_count);

// Method to draw a 1x1 square centered at 0, 0, 0 and facing towards the camera
void drawSquare();

// Method to draw a wall/square
void drawWall(int facing, float w, float h) ;

void drawBox(float l, float w, float h);

void drawCircle(float r, int v) ;

void drawCylinderBody(float r, float h, int v);

void drawCylinder(float r, float h, int v);


#endif
