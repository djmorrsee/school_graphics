#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

#include "vert.h"
#include "face.h"
#include "dj_primitives.h"

void drawFaces(face *f, int c) 
{

	int i;
	face fa;
		
	glBegin(GL_TRIANGLES);
	for(i = 0; i < c; ++i) 
	{
		fa = f[i];
		glNormal3f(fa.nx, fa.ny, fa.nz);
		glVertex3f(fa.a.x, fa.a.y, fa.a.z);
		glVertex3f(fa.b.x, fa.b.y, fa.b.z);
		glVertex3f(fa.c.x, fa.c.y, fa.c.z);
	}
	
	glEnd();
}

void drawFace(face f)
{

	glBegin(GL_TRIANGLES);
	glNormal3f(f.nx, f.ny, f.nz);
	glVertex3f(f.a.x, f.a.y, f.a.z);

	glNormal3f(f.nx, f.ny, f.nz);
	glVertex3f(f.b.x, f.b.y, f.b.z);
	glNormal3f(f.nx, f.ny, f.nz);

	glVertex3f(f.c.x, f.c.y, f.c.z);
	glEnd();
}

// Method to draw a 1x1 square centered at 0, 0, 0 and facing towards the camera
void drawSquare()
{
	
	const float p = 0.5;
	/*
	const int num_faces = 2;
	
	vert verts[4];
	face faces[2];
	
	replaceVert(&verts[0], -p, -p, 0);
	replaceVert(&verts[1], p, p, 0);
	replaceVert(&verts[2], -p, p, 0);
	replaceVert(&verts[3], p, -p, 0);
	
	replaceFace(&faces[0], verts[0], verts[1], verts[2]);
	replaceFace(&faces[1], verts[0], verts[3], verts[1]);
	
	drawFaces(faces, 2);
	*/
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(-p, p, 0);
	glVertex3f(p, p, 0);
	glVertex3f(p, -p, 0);
	glVertex3f(-p, -p, 0);
	glEnd();
}

void drawBox(float w, float h, float l)
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

void drawRoom(float w, float h, float l)
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
	glRotatef(90, 0, -1, 0);
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
	glRotatef(90, -1, 0, 0);
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
		replaceFace(&faces[i], verts[v0], verts[v1], verts[v2]);
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
		
		replaceFace(&faces[i * 2], verts[idx2], verts[idx1], verts[idx0]);
		replaceFace(&faces[i * 2 + 1], verts[idx2], verts[idx3], verts[idx1]);
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
vert getMidIcoPoint(vert a, vert b) 
{
	vert v;
	float midx = (a.x + b.x) / 2.0;
	float midy = (a.y + b.y) / 2.0;
	float midz = (a.z + b.z) / 2.0;
	replaceVert(&v, midx, midy, midz);
	return v;
}

face* refineIcoFaces(face *faces, int count, int num) 
{
	
	face *reFaced = malloc(sizeof(face) * 4 * count);
	
	face f;
	vert v0, v1, v2;

	int i, idx;
	for (i = 0; i < count; ++i) 
	{
		idx = i * 4;
		f = faces[i];
		
		v0 = f.a;
		v1 = f.b;
		v2 = f.c;
		
		
		vert a = getMidIcoPoint(v0, v1);
		vert b = getMidIcoPoint(v1, v2);
		vert c = getMidIcoPoint(v2, v0);
		
		// Make Points Unit Length
		normalize(&a);
		normalize(&b);
		normalize(&c);
		normalize(&v0);
		normalize(&v1);
		normalize(&v2);

		replaceFace(&reFaced[idx], v0, a, c);
		replaceFace(&reFaced[idx + 1], v1, b, a);
		replaceFace(&reFaced[idx + 2], v2, c, b);
		replaceFace(&reFaced[idx + 3], a, b, c);
		
	}
	if(num > 1) {
		return refineIcoFaces(reFaced, 4 * count, num-1);
	}
	return reFaced;
}

void drawIcosphere (int dim) 
{
	int i, idx;
	float t = (1.0 + sqrt(5.0)) / 2.0;
	vert verts[12];
	face faces[20];
	
	replaceVert(&verts[0], -1, t, 0);
	replaceVert(&verts[1], 1, t, 0);
	replaceVert(&verts[2], -1, -t, 0);
	replaceVert(&verts[3], 1, -t, 0);
	
	replaceVert(&verts[4], 0, -1, t);
	replaceVert(&verts[5], 0, 1, t);
	replaceVert(&verts[6], 0, -1, -t);
	replaceVert(&verts[7], 0, 1, -t);
	
	replaceVert(&verts[8], t, 0, -1);
	replaceVert(&verts[9], t, 0, 1);
	replaceVert(&verts[10], -t, 0, -1);
	replaceVert(&verts[11], -t, 0, 1);
	
	for (i = 0; i < 12; ++i) {
		normalize(&verts[i]);
	}
	
	// Faces
	replaceFace(&faces[0], verts[0], verts[11], verts[5]);
	replaceFace(&faces[1], verts[0], verts[5], verts[1]);
	replaceFace(&faces[2], verts[0], verts[1], verts[7]);
	replaceFace(&faces[3], verts[0], verts[7], verts[10]);
	replaceFace(&faces[4], verts[0], verts[10], verts[11]);
	
	replaceFace(&faces[5], verts[1], verts[5], verts[9]);
	replaceFace(&faces[6], verts[5], verts[11], verts[4]);
	replaceFace(&faces[7], verts[11], verts[10], verts[2]);
	replaceFace(&faces[8], verts[10], verts[7], verts[6]);
	replaceFace(&faces[9], verts[7], verts[1], verts[8]);
	
	replaceFace(&faces[10], verts[3], verts[9], verts[4]);
	replaceFace(&faces[11], verts[3], verts[4], verts[2]);
	replaceFace(&faces[12], verts[3], verts[2], verts[6]);
	replaceFace(&faces[13], verts[3], verts[6], verts[8]);
	replaceFace(&faces[14], verts[3], verts[8], verts[9]);
	
	replaceFace(&faces[15], verts[4], verts[9], verts[5]);
	replaceFace(&faces[16], verts[2], verts[4], verts[11]);
	replaceFace(&faces[17], verts[6], verts[2], verts[10]);
	replaceFace(&faces[18], verts[8], verts[6], verts[7]);
	replaceFace(&faces[19], verts[9], verts[8], verts[1]);
		
	if(dim > 0) {	
	
		face *refFaces = refineIcoFaces(faces, 20, dim);

		drawFaces(refFaces, 20 * pow(4, dim));
	} else {
		drawFaces(faces, 20);
	}

}
