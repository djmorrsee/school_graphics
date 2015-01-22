#define GL_GLEXT_PROTOTYPES

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "djgraphics.h"

// Scene Variables //
static int window_size = 600;

static float rot_amount = 5;
static float xRot = 0;
static float yRot = 0;

static bool useLight;
static bool usePersp;
static float fov;
static float dim;
static float asp;

// Texture Array // 
static unsigned int textures[16];

// OpenGL Draw Callback
static void display()
{

	//  Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//  Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	
	if(useLight)
		glEnable(GL_LIGHTING);

	//  Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	//  Undo previous transformations
	glLoadIdentity();

	// Scene Drawing Matrix
	glPushMatrix();

	vert lightPos = newVert(10, -10, 10, 0, 0);

	// Input Rotation
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	
	if(usePersp) 
	{
			// Using Perspective, Shift Scene Down //
			glTranslatef(0, -5, -10);
	}

	if(useLight)
		drawLight(.7, .7, .7, lightPos, .2, 0.1, 1);
	
	// Windows
	glPushMatrix();
	
	glTranslatef(0, 4.5, -2.45);
	glPushMatrix();
	glTranslatef(3, 0, 0);
	glScalef(2, 3, 10);
	drawTexturedBox(textures[2], 1, 1, .1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-3, 0, 0);
	glScalef(2, 3, 10);
	drawTexturedBox(textures[2], 1, 1, .1);
	glPopMatrix();
	
	glPopMatrix();
	
	// Door
	glPushMatrix();
	
	glTranslatef(0, 2.25, -2.45);
	glScalef(2.5, 4.5, 10);
	drawTexturedBox(textures[3], 1, 1, .1);
	
	glPopMatrix();
	
	// Building
	glPushMatrix();
	glTranslatef(0, 4, -5);
	glScalef(2, 2, 2);
	drawTexturedBox(textures[0], 6, 4, 3);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glScalef(20, 20, 1);
	drawTexturedSquare(textures[1], 4, 4);
	glPopMatrix();
	
	// Roof
	glPushMatrix();
	glTranslatef(0, 8.4, -5);
	glScalef(2, 2, 2);
	drawTexturedRoof(textures[5], 6.5, 2.5, 2);
	glPopMatrix();
	
	// Path
	glPushMatrix();
	glScalef(3, 1, 3);
	drawTexturedBox(textures[4], 1, .1, 5);
	glPopMatrix();
	
	// Things That Don't Need Light // 
	glDisable(GL_LIGHTING);
	
	// Things That Don't Need Textures //
	glDisable(GL_TEXTURE_2D);
	
	// Pop Scene Matrix
	glPopMatrix(); 	

	// Log
	glColor3f(1, 1, 1);
	glWindowPos2i(5, 5);
	Print("Texture Scene -- Rot(%.2f, %.2f) -- Persp(%s) -- Light(%s)", xRot, yRot, usePersp ? "Persp" : "Ortho", useLight ? "on" : "off");
	
	glFlush();
	glutSwapBuffers();

}

static void special(int key,int x,int y)
{

	//  Right arrow key
	if (key == GLUT_KEY_RIGHT)
		yRot+=rot_amount;
	//  Left arrow key
	else if (key == GLUT_KEY_LEFT)
		yRot-=rot_amount;
	//  Up arrow key
	else if (key == GLUT_KEY_UP)
		xRot += rot_amount;
	//  Down arrow key
	else if (key == GLUT_KEY_DOWN)
		xRot -= rot_amount;



	//  Reproject and Redisplay // 
	Project(fov, dim, asp, usePersp);
	glutPostRedisplay();
}

static void key(unsigned char ch,int x,int y)
{
	if(ch == 'k') 
		usePersp = !usePersp;
		
	else if (ch == 'l')
		useLight = !useLight;

	//  Reproject and Redisplay // 
	Project(fov, dim, asp, usePersp);
	glutPostRedisplay();
}

static void reshape(int width, int height)
{
	//  Reproject
	glViewport(0, 0, width, height);
	

	//  Reproject and Redisplay // 
	Project(fov, dim, asp, usePersp);
	glutPostRedisplay();
}

static void idle() 
{
	//  Reproject and Redisplay // 
	//  Project(fov, dim, asp);
	//  glutPostRedisplay();
}

static void sceneInit ()
{
	// GL Settings //
	glClearColor(0.2, 0.2, 0.2, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	
	// Set Up Projections
	usePersp = true;
	useLight = true;
	GetDefaultProjectionValues(&fov, &dim, &asp);
	
	textures[0] = LoadBMPTexture("tex/brick.bmp");
	textures[1] = LoadBMPTexture("tex/grass.bmp");
	textures[2] = LoadBMPTexture("tex/window.bmp");
	textures[3] = LoadBMPTexture("tex/door.bmp");
	textures[4] = LoadBMPTexture("tex/path.bmp");
	textures[5] = LoadBMPTexture("tex/roof.bmp");
}

int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(window_size, window_size);

	glutCreateWindow("Textured Scene!!");
	sceneInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutSpecialFunc(special);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}
