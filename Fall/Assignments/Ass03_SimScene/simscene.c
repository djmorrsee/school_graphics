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

#ifndef M_PI
#define M_PI 3.14159265
#endif

//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415927/180*(th))
#define Sin(th) sin(3.1415927/180*(th))

typedef struct
{
	float x;
	float y;
	float z;
} vert; 

static void replaceVert(vert* v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}


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

// Helper Method for Drawing a sequence of vertices.
// Verts contains all possible verts
// indices is a sequence of verts indexes that define faces.
static void drawVerts(vert* verts, int* indices, int i_count) 
{
	int i;

	glBegin(GL_TRIANGLES);
	for(i = 0; i < i_count; ++i) 
	{
		glVertex3f(verts[indices[i]].x, verts[indices[i]].y, verts[indices[i]].z);
	}
	glEnd();
}

// Method to draw a 1x1 square centered at 0, 0, 0 and facing towards the camera
static void drawSquare()
{
	const float p = 0.5;
	vert verts[4];	
	int tris[6];

	replaceVert(&verts[0], -p, -p, 0);
	replaceVert(&verts[1], p, -p, 0);
	replaceVert(&verts[2], p, p, 0);
	replaceVert(&verts[3], -p, p, 0);

	tris[0] = 0;
	tris[1] = 1;
	tris[2] = 2;
	tris[3] = 2;
	tris[4] = 3;
	tris[5] = 0;
	
	drawVerts(verts, tris, 6);
}

// Method to draw a wall/square
static void drawWall(int facing, float w, float h, vert pos) 
{
	
	int i, idx;

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
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
	
	drawSquare();
	glPopMatrix();
}


static void drawRoom() 
{

	vert pos;
	replaceVert(&pos, 0, -2.5, 0);

	glColor3f(0.3, 0.3, 0.3); // Floor/Ceiling
	drawWall(5, 5,5, pos);

	replaceVert(&pos, 0, 2.5, 0);
	drawWall(4, 5,5, pos);
	
	glColor3f(1, 1, 1); // Far Wall
	replaceVert(&pos, 0, 0, -2.5);
	drawWall(0, 5,5, pos);
	
	glColor3f(0.6, 0.6, 0.6);// Side Walls
	replaceVert(&pos, -2.5, 0, 0);
	drawWall(2, 5,5, pos);
	replaceVert(&pos, 2.5, 0, 0);
	drawWall(3, 5,5, pos);

}

static void drawBox(float l, float w, float h, vert pos)
{
	// New Position Vertex
	vert v;
	replaceVert(&v, pos.x, pos.y, pos.z + l / 2);

	glColor3f(0, 1, 1);
	drawWall(0, w, h, v);
	
	replaceVert(&v, pos.x, pos.y, pos.z-l/2);
	drawWall(1, w, h, v);

	glColor3f(1, 0, 0);

	replaceVert(&v, pos.x - w / 2, pos.y, pos.z);
	drawWall(3, l, h, v);

	glColor3f(0, 0, 1);
	
	replaceVert(&v, pos.x + w / 2, pos.y, pos.z);
	drawWall(2, l, h, v);

	glColor3f(0, 1, 0);

	replaceVert(&v, pos.x, pos.y - h / 2, pos.z);
	drawWall(4, w, l, v);

	replaceVert(&v, pos.x, pos.y + h / 2, pos.z);
	drawWall(5, w, l, v);


}

const int VERTS = 3;
static void drawCircle(float r, int v) 
{
	vert verts[v + 1];
	int i, j, ldx;
	int tris[v * VERTS];
	float x, y, z = 0;
	float angle;

	double slice = -2 * M_PI / v;

	replaceVert(&verts[0], 0, 0, 0);	

	for (i = 1; i <= v; ++i) 
	{	
		angle = slice * i;
		
		x = cos(angle) * r;
		z = sin(angle) * r;
	
		replaceVert(&verts[i], x, y, z);

	}

	for (i = 0; i < v; ++i) {
		ldx = i * VERTS;
		tris[ldx] = 0;
		tris[ldx + 1] = i + 1;

		if ( i == v - 1) 
			tris[ldx + 2] = 1;		
		else
			tris[ldx + 2] = i + 2;

	}

	drawVerts(verts, tris, v * VERTS);
	
}

static void drawCylinderBody(float r, float h, int v)
{
	vert verts[v * 2];

	int i, idx;
	int tris[v * VERTS * 2];

	float angle;
	float x, y, z;

	double slice = 2 * M_PI / v;
	for (i = 0; i < v; ++i) 
	{
		idx = i * 2;
	
		angle = slice * i;
		x = cos(angle) * r;
		y = h/2;
		z = sin(angle) * r;

		replaceVert(&verts[idx], x, y, z);
		replaceVert(&verts[idx + 1], x, -y, z);	
	}

	for(i = 0; i < v * 2; ++i)
	{
		idx = i * VERTS;
		tris[idx] = i;
 

			if (i % 2 == 0) 
			{
				tris[idx + 1] = (i + 2) % (v * 2);
				tris[idx + 2] = (i + 1) % (v * 2);
			} else {
				tris[idx + 1] = (i + 1) % (v * 2);
				tris[idx + 2] = (i + 2) % (v * 2);
			}

	}
	drawVerts(verts, tris, v * 2 * VERTS);

}

static void drawCylinder(float r, float h, vert pos, int v)
{

	glColor3f(0.8, 0.8, 0.8);
	
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);

	glPushMatrix();
	glTranslatef(0, h/2, 0);
	drawCircle(r, v);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -h/2, 0);
	glRotatef(180, 1, 0, 0);
	drawCircle(r, v);
	glPopMatrix();	

	glColor3f(.4, .1, .1);
	drawCylinderBody(r, h, v);
	glPopMatrix();
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

static int cyl_verts = 5;
static void display()
{
	// Position Vertex
	vert pos;
	replaceVert(&pos, 0, 0, 0);	

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
	glColor3f(1,1,1);

	// Draw Cylinder
	glPushMatrix();
	replaceVert(&pos, 0, 1.75, 0);
	drawCylinder(0.125, 1.5, pos, cyl_verts);	
	glPopMatrix();
	
	// Draw Box Method (Coordinates used as verts)
	replaceVert(&pos, -1.25, -1.25, 0);
	drawBox(1, 1, 2.5, pos);
	
	replaceVert(&pos, 1.25, 0, -2);
	drawBox(1, 2.5, 0.125, pos);

	glPushMatrix();
	
	// Draw Box Method, Translation 
	glTranslatef(2, -2, 1.5);

	replaceVert(&pos, 0, 0, 0);
	drawBox(1, 1, 1, pos);
	
	glPopMatrix();


	glColor3f(1, 1, 1);

	glWindowPos2i(5, 5);
	Print("Xrot: %.4f Yrot: %.4f", xrot, yrot);

   	glFlush();
	glutSwapBuffers();

}

const float rot_amount = 5;
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
	if (ch == '-' && cyl_verts > 3)
	{
		cyl_verts -= 1;
	} else if ((ch == '+' || ch == '=') && cyl_verts < 100)
	{
		cyl_verts += 1;
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

