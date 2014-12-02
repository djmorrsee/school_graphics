/*
 * 
 */
#include "dj.h"


double u = 5;
void draw_structure()
{
	float w = 7;
	float d = 5;
	float h = 1;
	glPushMatrix();
	glTranslatef(0, -h * u / 2, 0);
	drawWall(up, w*u, d*u, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, h * u / 2, 0);
	drawWall(down, w*u, d*u, 0);
	glPopMatrix();

	glColor3f(0.5, 0, 0.5);
	glPushMatrix();
	glTranslatef(0, 0, -d/2*u);
	drawWall(forward, w*u, h*u, 0);
	glPopMatrix();

	glColor3f(0.5, 0, 0);
	glPushMatrix();
	glTranslatef(-u/2, 0, u);
	drawWall(left, 3*u, h*u, 0);
	glPopMatrix();

	glColor3f(0.5, 0, 0);
	glPushMatrix();
	glTranslatef(u/2, 0, u);
	drawWall(right, 3*u, h*u, 0);
	glPopMatrix();
}

void draw_light()
{
	float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	float diffuse[] = { li_r, li_g, li_b, 1.0 };
	float specular[] = { 0, 0, 0, 1 };

	float pos[] = { li_d * Cos(li_zh), li_y, li_d * Sin(li_zh), 1 };

	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	float m[] = {GL_TRUE};
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, m);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

void display() 
{

	// Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	// Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	
	// Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	
	// Undo previous transformations
	glLoadIdentity();

	//float lv[3] = { vx_persp_loc + vlook_vector[0], vy_persp_loc + vlook_vector[1], vz_persp_loc + vlook_vector[2] };
	float x = vcamera_location[0] + vlook_vector[0];
	float y = vcamera_location[1] + vlook_vector[1];
	float z = vcamera_location[2] + vlook_vector[2];

	gluLookAt(vcamera_location[0],vcamera_location[1],vcamera_location[2] , x,y,z , 0,1,0);

	glColor3f(.8,.8,.8);

	draw_structure();

	// Log
	glColor3f(1, 1, 1);
	glWindowPos2i(5, 5);
	Print("Rotation: %.3f %.3f %.3f", vlook_vector[0], vlook_vector[1], vlook_vector[2]);


	glFlush();
	glutSwapBuffers();
}
