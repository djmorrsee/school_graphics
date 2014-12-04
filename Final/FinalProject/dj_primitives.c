/*
 * dj_primitives.c
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 */

#include "dj.h"

void drawPoint(vert v, vector3 normal)
{
	// This function assumes we are inside a glBegin(GL_TRIANGLES) block
	// Probably shouldn't be called anywhere else but drawFace
	glTexCoord2f(v.tex_coord.x, v.tex_coord.y);
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(v.position.x, v.position.y, v.position.z);
}
void drawFace(face f)
{
	glBegin(GL_TRIANGLES);

	drawPoint(f.a, f.normal);
	drawPoint(f.b, f.normal);
	drawPoint(f.c, f.normal);

	glEnd();
}

void drawFaces(face *f, int count, int texture_id)
{
	int i;
	glBindTexture(GL_TEXTURE_2D, texture_id);
	for (i = 0; i < count; ++i)
	{
		drawFace(f[i]);
	}
}

void drawMesh(mesh m)
{
	drawFaces(m.faces, m.face_count, m.texture_id);
}

void drawSquare(double xa, double ya, int texture_id)
{
	static const float p = 0.5;
	vert verts[4];
	mesh m;

	m.face_count = 2;
	m.texture_id = texture_id;

	verts[0] = new_vert(-p, -p, 0,	0, 0);
	verts[1] = new_vert(p, p, 0, 	xa, ya);
	verts[2] = new_vert(-p, p, 0, 	0, ya);
	verts[3] = new_vert(p, -p, 0, 	xa, 0);

	m.faces[0] = new_face(verts[0], verts[1], verts[2]);
	m.faces[1] = new_face(verts[3], verts[1], verts[0]);

	drawMesh(m);
}

void drawWall(facing_t dir, double length, double height, int texture_id)
{
	glPushMatrix();


	switch(dir)
	{
	case left:
		glRotatef(90, 0, 1, 0);
		break;
	case right:
		glRotatef(90, 0, -1, 0);
		break;
	case forward:
		break;
	case backward:
		glRotatef(180, 0, 1, 0);
		break;
	case up:
		glRotatef(90, -1, 0, 0);
		break;
	case down:
		glRotatef(90, 1, 0, 0);
		break;
	}



	glScalef(length, height, 1);
	drawSquare(length, height, texture_id);
	glPopMatrix();
}

void draw_structure()
{
	static float hm = 4;
	static float tm = 2;


	// Structure Piece A
	// Draw Floor
	glPushMatrix();
	glTranslatef(0, -hm/2, 0);
	drawWall(up, hm, hm, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, hm/2, 0);
	drawWall(down, hm, hm, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-hm/2, 0, 0);
	drawWall(left, hm, hm, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -hm/2);
	drawWall(forward, hm, hm, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, hm/2);
	drawWall(backward, hm, hm, 0);
	glPopMatrix();
}
