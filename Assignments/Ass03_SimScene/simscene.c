#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

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

static void drawWall(int facing, float w, float h, float x, float y, float z) 
{
	glPushMatrix();
	glTranslatef(x, y, z);
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

	const float p = 0.5;
	glBegin(GL_TRIANGLES);
	glVertex3f(-p, -p, 0);
	glVertex3f(p, -p, 0);
	glVertex3f(p, p, 0);

	glVertex3f(p, p, 0);
	glVertex3f(-p, p, 0);
	glVertex3f(-p, -p, 0);
	glEnd();
	glPopMatrix();
}


static void drawRoom() 
{
	glColor3f(0.3, 0.3, 0.3); // Floor/Ceiling
	drawWall(5, 5,5, 0,-2.5,0);
	drawWall(4, 5,5, 0, 2.5,0);
	
	glColor3f(1, 1, 1); // Far Wall
	drawWall(0, 5,5, 0,0,-2.5);
	
	glColor3f(0.6, 0.6, 0.6);// Side Walls
	drawWall(2, 5,5, -2.5,0,0);
	drawWall(3, 5,5,  2.5,0,0);
}

static void drawBox(float l, float w, float h, float x, float y, float z)
{
	glColor3f(0, 1, 1);
	drawWall(0, w, h, x, y, z + l / 2);
	drawWall(1, w, h, x, y, z - l / 2);

	glColor3f(1, 0, 0);
	drawWall(3, l, h, x - w / 2, y, z);

	glColor3f(0, 0, 1);
	drawWall(2, l, h, x + w / 2, y, z);

	glColor3f(0, 1, 0);
	drawWall(4, w, l, x, y - h / 2, z);
	drawWall(5, w, l, x, y + h / 2, z);
}

/*
 *  Set projection
 */
static float dim = 3;
static int window_size = 600;
static void Project()
{

	//glViewport(0, 0, window_size, window_size);
   //  Tell OpenGL we want to manipulate the projection matrix
	glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
	glLoadIdentity();
	glOrtho(-dim, dim, -dim, dim, -dim * 2, dim * 2);

	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

// OpenGL Draw Callback
static float xrot = 0;
static float yrot = 0;
static void display()
{
	
	//  Erase the window and the depth buffer
   	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   	//  Enable Z-buffering in OpenGL
   	glEnable(GL_DEPTH_TEST);
   	//  Undo previous transformations
   	glLoadIdentity();

	//  Switch to manipulating the model matrix
  	glMatrixMode(GL_MODELVIEW);
   	//  Undo previous transformations
   	glLoadIdentity();
	
	// User Rotation
	glRotatef(xrot, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);

	// Main Room
	drawRoom();
	
	// Draw Box Method (Coordinates used as verts)
	drawBox(1, 1, 2.5, -1.25, -1.25, 0);
	drawBox(1, 2.5, 0.125, 1.25, 0, -2);

	glPushMatrix();
	
	// Draw Box Method, Translation 
	glTranslatef(2, -2, 1.5);
	drawBox(1, 1, 1, 0, 0, 0);
	
	glPopMatrix();


	glColor3f(1, 1, 1);

	glWindowPos2i(5, 5);
	Print("Xrot: %.4f Yrot: %.4f", xrot, yrot);

   	glFlush();
	glutSwapBuffers();

}

const float rot_amount = 0.5;
static void special(int key,int x,int y)
{
	//  Right arrow key 
   	if (key == GLUT_KEY_RIGHT) 
		yrot+=rot_amount;
   	//  Left arrow key 
   	else if (key == GLUT_KEY_LEFT)
		yrot-=rot_amount;
   	//  Up arrow key
   	else if (key == GLUT_KEY_UP)
		xrot += rot_amount;
   	//  Down arrow key
   	else if (key == GLUT_KEY_DOWN)
		xrot -= rot_amount;
	
	//  Reproject
   	Project();
   	//  Tell GLUT it is necessary to redisplay the scene
   	glutPostRedisplay();
}

static void key(unsigned char ch,int x,int y) 
{
	//if (ch == 'q') {
	//	s += _ds;
	//	CalculatePoints();
	//}
	
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

static void init () 
{
	glEnable(GL_CULL_FACE);
}


int main(int argc, char *argv[]) 
{
	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(window_size, window_size);

 	glutCreateWindow("Simple Scene!");
	init();

 	glutDisplayFunc(display);
 	glutReshapeFunc(reshape);
  	glutKeyboardFunc(key);
  	glutSpecialFunc(special);

 	glutMainLoop();

	return 0;
}

