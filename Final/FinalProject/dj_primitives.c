/*
 * dj_primitives.c
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 */

#include "dj.h"

void drawPoint(vert v, vector3 normal) {
	// This function assumes we are inside a glBegin() block
	// Probably shouldn't be called anywhere else but drawFace
	glTexCoord2f(v.tex_coord.x, v.tex_coord.y);
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(v.position.x, v.position.y, v.position.z);
}
void drawFace(face f) {
	glBegin(GL_TRIANGLES);

	drawPoint(f.a, f.normal);
	drawPoint(f.b, f.normal);
	drawPoint(f.c, f.normal);

	glEnd();
}

void drawFaces(face *f, int count, int texture_id) {
	int i;
	glBindTexture(GL_TEXTURE_2D, texture_id);
	for (i = 0; i < count; ++i) {
		drawFace(f[i]);
	}
}

void drawMesh(mesh m) {
	drawFaces(m.faces, m.face_count, m.texture_id);
}

void drawPlane(int res, int texture_id, float tws, float ths) {
	// Draws a planar plane. Each vertex will have parallel normals. Do transforms after this call
	int i, j, k;
//	int index, v_count;
	float p = 1.0 / res;

//	v_count = 2 * res * res + 2 * res; // Recurrance Relations!

	vector3 normal = { .x = 0, .y = 0, .z = -1 };

	glRotatef(180, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	for (i = 0; i < res; ++i) {
		glBegin(GL_QUAD_STRIP);

		for (j = 0; j <= res; ++j) {
			for (k = 0; k < 2; ++k) {
				vert v;
				vector3 point = { .x = j * p - 0.5, .y = i * p + k * p - 0.5,
						.z = 0 };

				vector2 tex = { .x = (point.x + 0.5) / tws, .y = (point.y + 0.5)
						/ ths };

				v.position = point;
				v.tex_coord = tex;

//				index = k + 2 * (j + i * (res + 1)); // Loop Arithmetic!
				drawPoint(v, normal);
			}
		}
		glEnd();
	}

}

void drawWall(facing_t dir, double length, double height, int texture_id,
		float tws, float ths) {
	glPushMatrix();

	switch (dir) {
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
	drawPlane(4, texture_id, tws, ths);
	glPopMatrix();
}

void draw_doors(float scale) {
	glPushMatrix();

	glPushMatrix();

	glTranslatef(0, -.25, 0);
	glScalef(0.6, 0.85, 1);
	glScalef(scale, scale, 1);
	drawWall(forward, 1, 1, v_textures[3], 1, 1);
	glPopMatrix();
	glPopMatrix();
}

vector3 z;
vector4 r;
void draw_structure() {
	static float hm = 4;

	// Structure Piece A
	// Draw Floor
	glPushMatrix();


	glTranslatef(-hm, 0, hm / 2);
	set_light(3, 0, 1.5, 0, 1, 0, 0);
	draw_light(3);

	glPushMatrix();
	glTranslatef(0, -hm / 2, 0);
	drawWall(up, hm, hm, v_textures[0], 1.0 / 2, 1.0 / 2);
	glPopMatrix();

	// Draw Ceiling
	glPushMatrix();
	glTranslatef(0, hm / 2, 0);
	drawWall(down, hm, hm, v_textures[2], 1, 1);
	glPopMatrix();

	// Draw Walls
	glPushMatrix();
	glTranslatef(-hm / 2, 0, 0);
	drawWall(left, hm, hm, v_textures[1], 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -hm / 2);
	drawWall(forward, hm, hm, v_textures[1], 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, hm / 2);
	drawWall(backward, hm, hm, v_textures[1], 1, 1);
	glPopMatrix();

	glPopMatrix();
//
//	// Section B
	glPushMatrix();

	set_light(1, 0, 1.8, 0, .6, .6, .6);
	draw_light(1);

	glPushMatrix();
	glTranslatef(0, -hm / 2, 0);
	drawWall(up, hm, hm * 6, v_textures[0], 2.0, 1.0 / 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, hm / 2, 0);
	drawWall(down, hm, hm * 6, v_textures[2], 1, 1.0 / 6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(hm / 2, 0, 0);
	drawWall(right, hm * 6, hm, v_textures[1], 1.0 / 6, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, hm * 3);

	glPushMatrix();
	set_light(0, 0, 1.8, -1, .6, .6, .6);
	draw_light(0);
	glPopMatrix();

	drawWall(backward, hm, hm, v_textures[1], 1, 1);
	glRotatef(180, 0, 1, 0);
	glTranslatef(0, 0, 0.5);
	draw_doors(hm);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-hm / 2, 0, -1.5 * hm);
	drawWall(left, hm * 3, hm, v_textures[1], 1.0 / 2, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-hm / 2, 0, 2 * hm);
	drawWall(left, hm * 2, hm, v_textures[1], 1.0 / 3, 1);
	glPopMatrix();

	glPopMatrix();
//
//	// Section C
	glPushMatrix();

	glTranslatef(0, 0, -3.5 * hm);

	set_light(4, 0, 1.8, 0, .6, .6, .6);
	draw_light(4);

	glPushMatrix();
	glTranslatef(0, -hm / 2, 0);
	drawWall(up, 5 * hm, hm, v_textures[0], 1.0 / 5, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, hm / 2, 0);
	drawWall(down, 5 * hm, hm, v_textures[2], 1.0 / 5, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -hm / 2);
	drawWall(forward, 5 * hm, hm, v_textures[1], 1.0 / 2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5 * hm, 0, hm / 2);
	drawWall(backward, 2 * hm, hm, v_textures[1], 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5 * hm, 0, hm / 2);
	drawWall(backward, 2 * hm, hm, v_textures[1], 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5 * hm, 0, 0);
	drawWall(right, hm, hm, v_textures[1], 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5 * hm, 0, 0);
	set_light(2, 1, 1.8, 0, .6, .6, .6);
	draw_light(2);
	drawWall(left, hm, hm, v_textures[1], 1, 1);
	glPopMatrix();

	glPopMatrix();
}
