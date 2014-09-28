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

int xrot=0;
int yrot=0;
double asp=1;     //  Aspect ratio
double dim=50.0;   //  Size of world

//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415927/180*(th))
#define Sin(th) sin(3.1415927/180*(th))

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


typedef struct 
{
	double x;
	double y;
	double z;
} Point;

// Color // 
static float rate = 0.05f;
static Point color;
static void LerpColor () 
{
	color.x += rate;
	color.y += rate;
	color.z += rate;
	
	color.x = color.x > 1 ? 0 : color.x;
	color.y = color.y > 1 ? 0 : color.y;
	color.z = color.z > 1 ? 0 : color.z;
}

/*  Lorenz Parameters  */
static double dt = 0.001;

static double s  = 10;
static double b  = 2.6666;
static double r  = 20;

static const double _ds = 0.1;
static const double _db = 0.001;
static const double _dr = 0.05;

const static int MAX_POINTS = 100000;
static Point *points; 

static Point NextLorenzPoint (Point point) 
{
	double dx = s*(point.y-point.x);
	double dy = point.x*(r-point.z)-point.y;
	double dz = point.x*point.y - b*point.z;
	point.x += dt*dx;
	point.y += dt*dy;
	point.z += dt*dz;
	return point;
}

static void CalculatePoints () 
{
	int i;
	double start = (double)rand()/(double)RAND_MAX;

	srand(time(NULL));
	
	color.x = start;
	color.y = start;
	color.z = start;
	
	for (i = 0; i < MAX_POINTS - 1; ++i)
	{
		points[i + 1] = NextLorenzPoint(points[i]);
	}
}

// Primary Curve Drawing Function
static void draw_lorenz_points () 
{

	int i = 0;
	glBegin(GL_LINES);
	for (i = 1; i < MAX_POINTS; ++i) 
	{
		Point start = points[i - 1];
		Point end = points[i];
		
		glColor3f(color.x, color.y, color.z);
		LerpColor();

		glVertex3f(start.x, start.y, start.z);
		glVertex3f(end.x, end.y, end.z);
	}
	glEnd();
}

// OpenGL Draw Callback
static void display()
{
	//  Erase the window and the depth buffer
   	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   	//  Enable Z-buffering in OpenGL
   	glEnable(GL_DEPTH_TEST);
   	//  Undo previous transformations
   	glLoadIdentity();
   	
	glRotatef(xrot, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);
	glTranslatef(-r/2, -r/2, 0);
	draw_lorenz_points();


	glColor3f(1,1,1);
	glWindowPos2i(5, 5);
	Print("Lorenz Params - s: %f, b: %f, r: %f", s, b, r);

   	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

/*
 *  Set projection
 */
static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();

   glOrtho(-dim*asp, dim*asp, -dim, dim, -dim, dim);

   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

static void special(int key,int x,int y)
{
	
	//  Right arrow key - increase angle by 5 degrees
   	if (key == GLUT_KEY_RIGHT)
      		yrot += 5;
   	//  Left arrow key - decrease angle by 5 degrees
   	else if (key == GLUT_KEY_LEFT)
      		yrot -= 5;
   	//  Up arrow key - increase elevation by 5 degrees
   	else if (key == GLUT_KEY_UP)
      		xrot += 5;
   	//  Down arrow key - decrease elevation by 5 degrees
   	else if (key == GLUT_KEY_DOWN)
      		xrot -= 5;
   	//  Keep angles to +/-360 degrees

   	xrot %= 360;
   	yrot %= 360;
	
	//  Reproject
   	Project();
   	//  Tell GLUT it is necessary to redisplay the scene
   	glutPostRedisplay();
}

static void key(unsigned char ch,int x,int y) 
{
	if (ch == 'q') {
		s += _ds;
		CalculatePoints();
	}
	else if (ch == 'a') {
		s -= _ds;
		CalculatePoints();
	}
	else if (ch == 'w') {
		b += _db;
		CalculatePoints();
	}
	else if (ch == 's') {
		b -= _db;
		CalculatePoints();
	}
	else if (ch == 'e') {
		r += _dr;
		CalculatePoints();
	}
	else if (ch == 'd') {
		r -= _dr;
		CalculatePoints();
	}
	//  Reproject
   	Project();
   	//  Tell GLUT it is necessary to redisplay the scene
   	glutPostRedisplay();
}

static void reshape(int width, int height) 
{
	//  Reproject
	asp = (double)width/(double)height;
	glViewport(0, 0, width, height);
   	Project();
}

static void init () 
{
	glDisable(GL_LIGHTING);

	points = malloc(MAX_POINTS * sizeof(Point));

	Point point;

	point.x = 1;
	point.y = 1;
	point.z = 1;

	points[0] = point;

	CalculatePoints();
	
}

static int window_size = 600;
int main(int argc, char *argv[]) 
{
	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(window_size, window_size);

 	glutCreateWindow("Lorenz Attractor");
	init();

 	glutDisplayFunc(display);
 	glutReshapeFunc(reshape);
  	glutKeyboardFunc(key);
  	glutSpecialFunc(special);

 	glutMainLoop();

	return 0;
}

