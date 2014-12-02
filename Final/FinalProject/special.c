/*
 * 
 */
#include "dj.h"
void special(int key, int x, int y)
{
	//  Right arrow key - increase angle by 5 degrees
	if (key == GLUT_KEY_RIGHT)
		Rotate(rot_speed, 0);
	//  Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT)
		Rotate(-rot_speed, 0);
	//  Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_UP)
		Rotate(0, rot_speed);
	//  Down arrow key - decrease elevation by 5 degrees
	else if (key == GLUT_KEY_DOWN)
		Rotate(0, -rot_speed);
	//  PageUp key - increase dim
	//else if (key == GLUT_KEY_PAGE_DOWN)
	//  PageDown key - decrease dim
	//else if (key == GLUT_KEY_PAGE_UP && dim>1)
	//  Keep angles to +/-360 degrees

	//  Update projection
	Project();
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}
