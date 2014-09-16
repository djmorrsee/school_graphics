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

int axes=0;       //  Display axes
int mode=0;       //  Projection mode
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=35;       //  Field of view (for perspective)
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

/*
 *  Set projection
 */
static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (mode)
      gluPerspective(fov,asp,dim/4,4*dim);
   //  Orthogonal projection
   else
      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

typedef struct 
{
	double x;
	double y;
	double z;
} Point;


/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;

double dt = 0.001;

Point NextLorenzPoint (Point point) 
{
	double dx = s*(point.y-point.x);
	double dy = point.x*(r-point.z)-point.y;
	double dz = point.x*point.y - b*point.z;
	point.x += dt*dx;
	point.y += dt*dy;
	point.z += dt*dz;
	return point;
}

float rate = 0.05f;
Point color;

void LerpColor () 
{
	color.x += rate;
	color.y += rate;
	color.z += rate;
	
	color.x = color.x > 1 ? 0 : color.x;
	color.y = color.y > 1 ? 0 : color.y;
	color.z = color.z > 1 ? 0 : color.z;
}


const int MAX_POINTS = 100000;
Point *points; 

void draw_lorenz_points () 
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

void display()
{
	//  Erase the window and the depth buffer
   	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   	//  Enable Z-buffering in OpenGL
   	glEnable(GL_DEPTH_TEST);
   	//  Undo previous transformations
   	glLoadIdentity();

   	//  Perspective - set eye position
   	if (mode)
   	{
		double Ex = 10*-dim*Sin(th)*Cos(ph);
      		double Ey = +dim        *Sin(ph);
      		double Ez = +dim*Cos(th)*Cos(ph);
      		gluLookAt(50,0,50, -10,10,10 , 0,Cos(ph),0);
   	}
   	//  Orthogonal - set world orientation
   	else
   	{
   		glRotatef(ph,1,0,0);
      		glRotatef(th,0,1,0);
   	}

	draw_lorenz_points();

   	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void special(int key,int x,int y)
{
	//  Right arrow key - increase angle by 5 degrees
   	if (key == GLUT_KEY_RIGHT)
      		th += 5;
   	//  Left arrow key - decrease angle by 5 degrees
   	else if (key == GLUT_KEY_LEFT)
      		th -= 5;
   	//  Up arrow key - increase elevation by 5 degrees
   	else if (key == GLUT_KEY_UP)
      		ph += 5;
   	//  Down arrow key - decrease elevation by 5 degrees
   	else if (key == GLUT_KEY_DOWN)
      		ph -= 5;

   	//  Keep angles to +/-360 degrees
   	th %= 360;
   	ph %= 360;
	//  Reproject
   	Project();
   	//  Tell GLUT it is necessary to redisplay the scene
   	glutPostRedisplay();
}

void key(unsigned char ch,int x,int y) 
{
	if (ch == 'f')
		dim += 0.1;
	else if (ch == 'v' && dim > 1)
		dim -= 0.1;
	//  Reproject
   	Project();
   	//  Tell GLUT it is necessary to redisplay the scene
   	glutPostRedisplay();
}

void reshape(int width, int height) 
{
	//  Reproject
   	Project();

}

void init () 
{
	int i;
	Point point;

	point.x = 1;
	point.y = 1;
	point.z = 1;

	points = malloc(MAX_POINTS * sizeof(Point));
	points[0] = point;

	srand(time(NULL));
	double start = (double)rand()/(double)RAND_MAX;
	color.x = start;
	color.y = start;
	color.z = start;
	
	for (i = 0; i < MAX_POINTS - 1; ++i)
	{
		points[i + 1] = NextLorenzPoint(points[i]);
	}
}

int window_size = 600;
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

