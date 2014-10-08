#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include <GL/glut.h>

#include "vert.h"
#include "face.h"
#include "dj_primitives.h"

#ifndef M_PI
#define M_PI 3.14159265
#endif

//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415927/180*(th))
#define Sin(th) sin(3.1415927/180*(th))

static float getRandPercent()
{
	return (float)rand() / (float)RAND_MAX;
}


///////////////////////////////

/*
*  Convenience routine to output raster text
*  Use VARARGS to make this more flexible
*/
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
	char    buf[LEN];
	char*   ch=buf;
	va_list args;
	//  Turn the parameters into a character string
	va_start(args,format);
	vsnprintf(buf,LEN,format,args);
	va_end(args);
	//  Display the characters one at a time at the current raster position
	while (*ch)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}


/*
*  Set projection
*/
// Ortho
static float oDim = 6;
static float clippingPlane = 50;

static float yRot = 0;
static float xRot = 0;

static float xPos = 0;
static float yPos = 0;
static float zPos = 0;

static bool usePerspective;

static void Project()
{

	//glViewport(0, 0, window_size, window_size);
	//  Tell OpenGL we want to manipulate the projection matrix
	glMatrixMode(GL_PROJECTION);
	//  Undo previous transformations
	glLoadIdentity();

	if(usePerspective == true) {
		gluPerspective(45, 1, 0.01, 1000);
	} else {
		glOrtho(-oDim, oDim, - oDim / 2, oDim, -clippingPlane, clippingPlane);
	}


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// OpenGL Draw Callback
static void display()
{

	//  Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//  Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	//  Undo previous transformations

	//  Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	//  Undo previous transformations
	glLoadIdentity();

	glColor3f(1, 1, 1);
	vert a;
	vert b;
	vert c;
	replaceVert(&a, 0, 0, 0);
	replaceVert(&b, 1, 0, 0);
	replaceVert(&c, 0, 1, 0);

	face f;
	replaceFace(&f, &a, &b, &c);

	drawFace(f);

	// Logg
	glColor3f(1, 1, 1);
	glWindowPos2i(5, 5);
	Print("xrot %.2f yrot %.2f", xRot, yRot);

	glFlush();
	glutSwapBuffers();

}

static float rot_amount = 3;
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


	//  Reproject
		Project();
		//  Tell GLUT it is necessary to redisplay the scene
		glutPostRedisplay();
}

static void key(unsigned char ch,int x,int y)
{
	if(ch == 'k') {
		if (usePerspective)
			usePerspective = false;
		else
			usePerspective = true;
	}


	//  Reproject
		Project();
		//  Tell GLUT it is necessary to redisplay the scene
		glutPostRedisplay();
}

static void reshape(int width, int height)
{
	//  Reproject
	glViewport(0, 0, width, height);
	Project();
}

static void sceneInit ()
{
	// GL Settings //
	glClearColor(0, 0, 0, 0);
	glEnable(GL_CULL_FACE);

	// Start in Orthographic View //
	usePerspective = false;
}

static int window_size = 600;
int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(window_size, window_size);

	glutCreateWindow("Lewis Litt Up Scene!");
	sceneInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutSpecialFunc(special);

	glutMainLoop();

	return 0;
}
