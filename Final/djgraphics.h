#ifndef DJGRAPHICS
#define DJGRAPHICS

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glut.h>

// loadbmptex.c
unsigned int LoadBMPTexture(const char* filepath);

// print.c
void Print(const char* format, ...);

// project.c
void Project (float fov, float dim, float asp, bool usePersp); 
void GetDefaultProjectionValues (float* fov, float* dim, float* asp);

// axes.c
void DrawAxes(float len);

// vert.c 
typedef struct
{
	float x;
	float y;
	float z;
	
	float tx;
	float ty;
} vert;

vert newVert(float x, float y, float z, float tx, float ty);
float distance(vert a, vert b);

// face.c
typedef struct
{
	// Normals
	float nx;
	float ny;
	float nz;

	// World Pos
	vert a;
	vert b;
	vert c;	

} face;

face newFace(vert a, vert b, vert c) ;
void printFace(face f);

// light.c
void drawLight(float r, float g, float b, vert pos, float amb, float spec, bool useSmooth);


// Primitive Draw Functions -- dj_primitives.c // 
void drawFaces(face *f, int c);
void drawFace(face f);

void drawSquare();
void drawTexturedSquare(unsigned int texID, float xa, float ya);
void drawTexturedCircle(unsigned int texID, int res);
void drawTexturedBox(unsigned int texID, float w, float h, float l);
void drawTexturedRoof(unsigned int texID, float w, float h, float l);

#endif
