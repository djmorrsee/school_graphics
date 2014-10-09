#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

#include "vert.h"
#include "face.h"
#include "dj_primitives.h"

void drawFaces(face *f, int c) 
{
	
	glBegin(GL_TRIANGLES);
	int i;
	for(i = 0; i < c; ++i) 
	{
		glNormal3f(f[i].nx, f[i].ny, f[i].nz);
		glVertex3f(f[i].a->x, f[i].a->y, f[i].a->z);
		glVertex3f(f[i].b->x, f[i].b->y, f[i].b->z);
		glVertex3f(f[i].c->x, f[i].c->y, f[i].c->z);
	}
	
	glEnd();
}

void drawFace(face f)
{
	glBegin(GL_TRIANGLES);
	glNormal3f(f.nx, f.ny, f.nz);
	glVertex3f(f.a->x, f.a->y, f.a->z);

	glNormal3f(f.nx, f.ny, f.nz);
	glVertex3f(f.b->x, f.b->y, f.b->z);
	glNormal3f(f.nx, f.ny, f.nz);

	glVertex3f(f.c->x, f.c->y, f.c->z);
	glEnd();
}

// Method to draw a 1x1 square centered at 0, 0, 0 and facing towards the camera
void drawSquare()
{
	const float p = 0.5;
	const int num_faces = 2;
	
	vert verts[4];
	face faces[2];
	
	replaceVert(&verts[0], -p, -p, 0);
	replaceVert(&verts[1], p, -p, 0);
	replaceVert(&verts[2], -p, p, 0);
	replaceVert(&verts[3], p, p, 0);
	
	/*
	glBegin(GL_LINES);
	glVertex3f(verts[0].x, verts[0].y, verts[0].z);
	glVertex3f(verts[1].x, verts[1].y, verts[1].z);
	glEnd();
	*/
	
	replaceFace(&faces[0], &verts[0], &verts[1], &verts[2]);
	replaceFace(&faces[1], &verts[3], &verts[2], &verts[1]);
	
	//drawFaces(faces, 2);
	drawFace(faces[0]);
	drawFace(faces[1]);
}

void drawRoom(float w, float h, float l)
{
	glPushMatrix();
	glTranslatef(0, 0, -l / 2);
	glScalef(w, h, 1);
	drawSquare();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, l / 2);
	glRotatef(180, 0, 1, 0);
	glScalef(w, h, 1);
	drawSquare();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-w / 2, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(l, h, 1);
	drawSquare();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(w / 2, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(l, h, 1);
	drawSquare();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, h / 2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(w, l, 1);
	drawSquare();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, -h / 2, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(w, l, 1);
	drawSquare();
	glPopMatrix();

}

void drawBox(float w, float h, float l)
{
	glPushMatrix();
	glTranslatef(0, 0, l / 2);
	glScalef(w, h, 1);
	drawSquare();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, -l / 2);
	glRotatef(180, 0, 1, 0);
	glScalef(w, h, 1);
	drawSquare();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(w / 2, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(l, h, 1);
	drawSquare();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-w / 2, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(l, h, 1);
	drawSquare();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -h / 2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(w, l, 1);
	drawSquare();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, h / 2, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(w, l, 1);
	drawSquare();
	glPopMatrix();

}

void drawCircle(float r, int v)
{
	vert verts[v + 1];
	face faces[v];
	
	int i;
	float x, y, angle;
	float slice = 2 * M_PI / (float)v;
	
	replaceVert(&verts[0], 0, 0, 0);
	for(i = 1; i <= v; ++i) {
		angle = slice * i;
		x = cos(angle) * r;
		y = sin(angle) * r;
		
		replaceVert(&verts[i], x, y, 0);
	}
	
	
	for(i = 0; i < v; ++i) 
	{
		int v0, v1, v2;
		v0 = 0;
		v1 = i + 1;
		v2 = i + 2 > v ? 1 : i + 2;
		replaceFace(&faces[i], &verts[v0], &verts[v1], &verts[v2]);
	}
	
	drawFaces(faces, v);
	
}

void drawCylinderBody(float r, float h, int v)
{
	vert verts[v * 2];
	face faces[v * 2];
	
	int i;
	float x, y, z, angle;
	float slice = 2 * M_PI / (float)v;
	
	for (i = 0; i < v; ++i) {
		angle = slice * i;
		x = cos(angle) * r;
		y = h / 2;
		z = sin(angle) * r;
		replaceVert(&verts[2 * i], x, y, z);
		replaceVert(&verts[2 * i + 1], x, -y, z);

	}
	
	for (i = 0; i < v; ++i) {
		// 0, 1, 2
		// 1, 3, 2
		
		// 2, 3, 4
		// 3, 5, 4
		int idx0 = i * 2;
		int idx1 = (idx0 + 1) % (v * 2);
		int idx2 = (idx0 + 2) % (v * 2);
		int idx3 = (idx0 + 3) % (v * 2);
		
		replaceFace(&faces[i * 2], &verts[idx2], &verts[idx1], &verts[idx0]);
		replaceFace(&faces[i * 2 + 1], &verts[idx2], &verts[idx3], &verts[idx1]);
	}
	
	drawFaces(faces, v * 2);

}

void drawCylinder(float r, float h, int v)
{
	glPushMatrix();
	glTranslatef(0, h / 2, 0);
	glRotatef(90, -1, 0, 0);
	drawCircle(r, v);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, -h / 2, 0);
	glRotatef(90, 1, 0, 0);
	drawCircle(r, v);
	glPopMatrix();
	
	drawCylinderBody(r, h, v);
}
