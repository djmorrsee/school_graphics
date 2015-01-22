#include <math.h>
#include <GL/glut.h>

#include "vert.h"
#include "dj_primitives.h"

// Helper Method for Drawing a sequence of vertices.
// Verts contains all possible verts
// indices is a sequence of verts indexes that define faces.
int VERTS = 3;
void drawVerts(vert* verts, int* indices, int i_count) 
{
	int i;

	glBegin(GL_TRIANGLES);
	for(i = 0; i < i_count; ++i) 
	{
		glVertex3f(verts[indices[i]].x, verts[indices[i]].y, verts[indices[i]].z);
	}
	glEnd();
}

// Method to draw a 1x1 square centered at 0, 0, 0 and facing towards the camera
void drawSquare()
{
	const float p = 0.5;
	vert verts[4];	
	int tris[6];

	replaceVert(&verts[0], -p, -p, 0);
	replaceVert(&verts[1], p, -p, 0);
	replaceVert(&verts[2], p, p, 0);
	replaceVert(&verts[3], -p, p, 0);

	tris[0] = 0;
	tris[1] = 1;
	tris[2] = 2;
	tris[3] = 2;
	tris[4] = 3;
	tris[5] = 0;
	
	drawVerts(verts, tris, 6);
}

// Method to draw a wall/square
void drawWall(int facing, float w, float h) 
{
	
	glPushMatrix();
	switch (facing) 
	{
	case 0: // towards camera
		break;
	case 1: // away from camera
		glRotatef(180, 0, 1, 0);
		break;
	case 2: // right facing (for left wall)
		glRotatef(90, 0, 1, 0);
		break;
	case 3: // left facing (for right wall)
		glRotatef(90, 0, -1, 0);
		break;
	case 4: // upwards facing (for floor)
		glRotatef(90, 1, 0, 0);
		break;
	case 5: // downwards facing
		glRotatef(90, -1, 0, 0);
		break;
	}
	glScalef(w, h, 1);
	
	drawSquare();
	glPopMatrix();
}

void drawBox(float w, float h, float l)
{
	
	glPushMatrix();
	glTranslatef(0, 0, l / 2);
	drawWall(0, w, h);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, -l/2);
	drawWall(1, w, h);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-w / 2, 0, 0);
	drawWall(3, l, h);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(w / 2, 0, 0);
	drawWall(2, l, h);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -h / 2, 0);
	drawWall(4, w, l);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, h / 2, 0);
	drawWall(5, w, l);
	glPopMatrix();

}

void drawCircle(float r, int v) 
{
	vert verts[v + 1];
	int i, ldx;
	int tris[v * VERTS];
	float x = 0, y = 0, z = 0;
	float angle;

	double slice = -2 * M_PI / v;

	replaceVert(&verts[0], 0, 0, 0);	

	for (i = 1; i <= v; ++i) 
	{	
		angle = slice * i;
		
		x = cos(angle) * r;
		z = sin(angle) * r;
	
		replaceVert(&verts[i], x, y, z);

	}

	for (i = 0; i < v; ++i) {
		ldx = i * VERTS;
		tris[ldx] = 0;
		tris[ldx + 1] = i + 1;

		if ( i == v - 1) 
			tris[ldx + 2] = 1;		
		else
			tris[ldx + 2] = i + 2;

	}

	drawVerts(verts, tris, v * VERTS);
	
}

void drawCylinderBody(float r, float h, int v)
{
	vert verts[v * 2];

	int i, idx;
	int tris[v * VERTS * 2];

	float angle;
	float x, y, z;

	double slice = 2 * M_PI / v;
	for (i = 0; i < v; ++i) 
	{
		idx = i * 2;
	
		angle = slice * i;
		x = cos(angle) * r;
		y = h/2;
		z = sin(angle) * r;

		replaceVert(&verts[idx], x, y, z);
		replaceVert(&verts[idx + 1], x, -y, z);	
	}

	for(i = 0; i < v * 2; ++i)
	{
		idx = i * VERTS;
		tris[idx] = i;
 

			if (i % 2 == 0) 
			{
				tris[idx + 1] = (i + 2) % (v * 2);
				tris[idx + 2] = (i + 1) % (v * 2);
			} else {
				tris[idx + 1] = (i + 1) % (v * 2);
				tris[idx + 2] = (i + 2) % (v * 2);
			}

	}
	drawVerts(verts, tris, v * 2 * VERTS);

}

void drawCylinder(float r, float h, int v)
{

	glColor3f(0.8, 0.8, 0.8);
	
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0, h/2, 0);
	drawCircle(r, v);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -h/2, 0);
	glRotatef(180, 1, 0, 0);
	drawCircle(r, v);
	glPopMatrix();	

	glColor3f(.4, .1, .1);
	drawCylinderBody(r, h, v);
	glPopMatrix();
}
