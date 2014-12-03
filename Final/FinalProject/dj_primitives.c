/*
 * dj_primitives.c
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 */

#include "dj.h"

void drawPoint(dj_vert v)
{
	// This function assumes we are inside a glBegin(GL_TRIANGLES) block
	// Probably shouldnt be called anywhere else but drawFace
	glTexCoord2f(v.tex_coords.x, v.tex_coords.y);
	glVertex3f(v.position.x, v.position.y, v.position.z);
}
void drawFace(dj_face f)
{
	glBegin(GL_TRIANGLES);
	glNormal3f(f.norm_x, f.norm_y, f.norm_z);

	drawPoint(f.a);
	drawPoint(f.b);
	drawPoint(f.c);

	glEnd();
}

void drawFaces(dj_face *f, int count, int texture_id)
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
	dj_vert verts[4];
	mesh m;

	m.face_count = 2;
	m.texture_id = texture_id;

	verts[0] = new_vert(-p, -p, 0,	0, 0);
	verts[1] = new_vert(p, p, 0, 	xa, ya);
	verts[2] = new_vert(-p, p, 0, 	0, ya);
	verts[3] = new_vert(p, -p, 0, 	xa, 0);

	m.faces[0] = new_face(verts[0], verts[1], verts[2]);
	m.faces[1] = new_face(verts[0], verts[3], verts[1]);

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
		glRotatef(180, 0, 1, 0);
		break;
	case backward:
		break;
	case up:
		glRotatef(90, 1, 0, 0);
		break;
	case down:
		glRotatef(90, -1, 0, 0);
		break;
	}



	glScalef(length, height, 1);
	drawSquare(length, height, texture_id);
	glPopMatrix();
}
