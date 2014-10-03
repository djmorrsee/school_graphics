#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include <GL/glut.h>

#include "vert.h"
#include "dj_primitives.h"

#ifndef M_PI
#define M_PI 3.14159265
#endif

//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415927/180*(th))
#define Sin(th) sin(3.1415927/180*(th))

float colors[24];
static float getRand() 
{
	return (float)rand() / (float)RAND_MAX;
}

// Perspscene Draw Functions //

void drawHouse (float h)
{
	float c[4];
	glGetFloatv(GL_CURRENT_COLOR, c);
	
	//glRotatef(90, 0, 1, 0);
	glTranslatef(0, h / 2.0, 0);
	glPushMatrix();
	
	drawBox(h, h, h);
	
	glPopMatrix();
	
	// Door
	glColor3f(c[0] - 0.1, c[1] - 0.1, c[2] - 0.1);
	glPushMatrix();
	
	glTranslatef(0, -h/3, h/2);
	drawBox(h / 5, h / 3, 0.05);
	
	glPopMatrix();
	
	// Windows
	glColor3f(c[0] - 0.2, c[1] - 0.2, c[2] - 0.2);
	glPushMatrix();
	
	glTranslatef(0, h / 6, h/2);
	glPushMatrix();
	glTranslatef(-h / 4, 0, 0);
	drawBox(h / 5, h / 5, 0.05);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(h / 4, 0, 0);
	drawBox(h / 5, h / 5, 0.05);
	glPopMatrix();
	
	glPopMatrix();
	
	// Roof
	glColor3f(c[0] - 0.3, c[1] - 0.3, c[2] - 0.3);
	glPushMatrix();
	
	glTranslatef(0, 7 * h / 12, 0);
	
	glPushMatrix();
	glTranslatef(-4 * h / 12, 0, 0);
	glRotatef(28, 0, 0, 1);
	glScalef(0.85, 1, 1);
	drawBox(h, 0.1, h);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(4 * h / 12, 0, 0);
	glRotatef(-28, 0, 0, 1);
	glScalef(0.85, 1, 1);
	drawBox(h, 0.1, h);
	glPopMatrix();
	
	glPopMatrix();
	
	
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
static float street_length = 40;
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

	// Drop Everything 1 Unit
   	glRotatef(yRot, 0, 1, 0);
   	glRotatef(xRot, 1, 0, 0);
   	   	glTranslatef(xPos, -1.5 + yPos, zPos);

   	
   	// Grass
   	glColor3f(0, 0.6, 0);
   	glPushMatrix();
   	glTranslatef(0, -.01, -street_length / 4);
   	drawBox(20, .1, street_length * 1.5);
   	glPopMatrix();
   	
	// Street
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(0, 0, -street_length / 4);
	drawBox(4, .1, street_length);
	glPopMatrix();
	
	// Sidewalks
	glColor3f(0.4, 0.4, 0.4);
	glPushMatrix();
	glTranslatef(2.5, 0.01, -street_length / 4);
	drawBox(1, 0.1, street_length);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-2.5, 0.01, -street_length / 4);
	drawBox(1, 0.1, street_length);
	glPopMatrix();
   	
   	// Houses
	glPushMatrix();
	
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, 0, -35);
   	drawHouse(5);
   	glPopMatrix();
   	
   	int i,j, z = 0;
   	float zpos = -20;
   	for (i = 0; i < 3; ++i) 
   	{
		for(j = 0; j < 2; ++j) 
		{
			
			glColor3f(colors[z++], colors[z++], colors[z++]);
			glPushMatrix();
			
			int neg = j == 0 ? 1 : -1;
			glTranslatef(7 * neg, 0, zpos);
			glRotatef(-90 * neg, 0, 1, 0);
			drawHouse(5);
			glPopMatrix();

		}
		zpos += 10;
		
	}
   	
   	
   	glPopMatrix();
   	
   	// Light Pole
   	glPushMatrix();
   	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(4, 2.5, -2);
   	drawCylinder(0.125, 5, 5);
   	glPopMatrix();
   	
   	// Logg
	glColor3f(0, 0, 0);
	glWindowPos2i(5, 5);
	
	Print("%s Loc(%.2f, %.2f, %.2f) Rot(%.2f, %.2f)", usePerspective == true ? "perspective" : "orthographic",
		xPos, yPos, zPos, xRot, yRot);

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
	if(ch == 'k') 
		if (usePerspective) 
			usePerspective = false;
		else
			usePerspective = true;
	
	else if (ch == 'w') 
	{
		zPos += 1;
	} else if (ch == 's') 
	{
		zPos -= 1;
	} else if (ch == 'd') 
	{
		xPos -= 1;
	} else if (ch == 'a') 
	{
		xPos += 1;
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
	glClearColor(0.8, 1, 1, 0);
	glEnable(GL_CULL_FACE);
	
	// Start in Orthographic View //
	usePerspective = false;
	
	// Setup Colors
	int i;
	for (i = 0; i < 24; ++i) 
	{
		colors[i] = getRand();
	}
}

static int window_size = 600;
int main(int argc, char *argv[]) 
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(window_size, window_size);

 	glutCreateWindow("Perspective Scene!");
	sceneInit();

 	glutDisplayFunc(display);
 	glutReshapeFunc(reshape);
  	glutKeyboardFunc(key);
  	glutSpecialFunc(special);

 	glutMainLoop();

	return 0;
}

