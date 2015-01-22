#define GL_GLEXT_PROTOTYPES

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
static float oDim = 10;
static float clippingPlane = 50;

static float yRot = 0;
static float xRot = 0;

static bool usePerspective;
static bool useLighting;
static bool useSmooth;

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
		glOrtho(-oDim, oDim, -oDim / 2, oDim + oDim / 2, -clippingPlane, clippingPlane);
	}


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// OpenGL Draw Callback
float li_zh, li_y;
float li_r, li_g, li_b;
float li_d;
void initLight() {
	li_zh = 90;
	li_y = -8;
	li_r = li_b = li_g = 0.8;
	li_d = 8;
}

void drawLight() {
	glShadeModel(useSmooth ? GL_SMOOTH : GL_FLAT);
	if (useLighting) {
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
		
		
	} else 
		glDisable(GL_LIGHTING);
}

static int resolution = 0;
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

		// Scene Drawing Matrix
	glPushMatrix();

	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);

	// Lighting Section //
	drawLight();
	
	if(usePerspective) {
		// Move Viewport Backwards and Up		
		glTranslatef(0, -2, -10);
	}

	// Scene
	glColor3f(.6, .6, .6);
	glPushMatrix();
	drawBox(15, 0.125, 15);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glColor3f(1, 1, 1);
	drawCylinder(0.5, 2, 4 + resolution * 4);
	
	glTranslatef(0, 1.5, 0);
	glColor3f(1, 1, 0);
	drawIcosphere(resolution);
	glPopMatrix();
	
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(3, .5, 1);
	glRotatef(45, 0, 1, 0);
	drawBox(4, 1, 1);
	glPopMatrix();

	// Things That Don't Need Light // 
	glDisable(GL_LIGHTING);
	
	// Draw Sphere As Light
	glPushMatrix();
	glColor3f(1, 1, .4);
	glTranslatef(-li_d * Cos(li_zh), -li_y, -li_d * Sin(li_zh));
	glScalef(.5, .5, .5);
	drawIcosphere(1);
	glPopMatrix();
	
	// Axes //
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_LINES);
	int len = 10;
	glVertex3d(-len, 0, 0);
	glVertex3d(len, 0, 0);
	glVertex3d(0, -len, 0);
	glVertex3d(0, len, 0);
	glVertex3d(0, 0, -len);
	glVertex3d(0, 0, len);
	glEnd();

	glPopMatrix();
	
	
	// Logg
	glColor3f(1, 1, 1);
	glWindowPos2i(5, 5);
	Print("K: %s Res: %d Dim: %f Smooth?: %s", usePerspective ? "Perspective" : "Ortho", resolution, oDim, useSmooth ? "YES" : "NO");
	
	glPopMatrix(); // Scene Drawing Matrix

	glFlush();
	glutSwapBuffers();

}

static float rot_amount = 3;
static void special(int key,int x,int y)
{

		//  Right arrow key
		if (key == GLUT_KEY_RIGHT && yRot < 30)
		yRot+=rot_amount;
		//  Left arrow key
		else if (key == GLUT_KEY_LEFT && yRot > -30)
		yRot-=rot_amount;
		//  Up arrow key
		else if (key == GLUT_KEY_UP && xRot < 30)
		xRot += rot_amount;
		//  Down arrow key
		else if (key == GLUT_KEY_DOWN && xRot > -30)
		xRot -= rot_amount;

	

	//  Reproject
		Project();
		//  Tell GLUT it is necessary to redisplay the scene
		glutPostRedisplay();
}

static float d_zh = .25;
static void key(unsigned char ch,int x,int y)
{
	if(ch == 'k') {
		usePerspective = !usePerspective;
	} else if (ch == 'l') {
		useLighting = !useLighting;
	} else if (ch == 'j') {
		useSmooth = !useSmooth;
	} else if (ch == 27) {
		exit(0);
	}

	else if (ch == 'w' && oDim > 5) {
		if(!usePerspective) {
			oDim--;
		}
	}
	
	else if (ch == 's' && oDim < 50) {
		if(!usePerspective) {
			oDim++;		}
	}
	
	else if (ch == 'a' && resolution > 0) {
		resolution -= 1;
	} 
	
	else if (ch == 'd' && resolution < 3) {
		resolution += 1;
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

static void idle() 
{
	li_zh += d_zh;
	Project();
	glutPostRedisplay();
}

static void sceneInit ()
{
	// GL Settings //
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Start in Orthographic View //
	usePerspective = false;
	useLighting = false;
	useSmooth = false;
	
	initLight();
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
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}
