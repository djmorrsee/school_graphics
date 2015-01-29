/*
 * 
 */
#include "../../dj.h"
void special(int key, int x, int y)
{
	//  Right arrow key - increase angle by 5 degrees
	if (key == GLUT_KEY_RIGHT)
		Move(right);
	//  Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT)
		Move(left);
	//  Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_UP)
		Move(forward);
	//  Down arrow key - decrease elevation by 5 degrees
	else if (key == GLUT_KEY_DOWN)
		Move(backward);
	//  PageUp key - increase dim
	else if (key == GLUT_KEY_PAGE_DOWN)
		v_dim = v_dim + 1;
	//  PageDown key - decrease dim
	else if (key == GLUT_KEY_PAGE_UP)
		v_dim = v_dim > 1 ? v_dim - 1 : v_dim;
	//  Keep angles to +/-360 degrees

	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}
