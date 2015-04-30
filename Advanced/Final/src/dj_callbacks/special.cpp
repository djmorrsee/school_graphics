/*
 * 
 */
#include "../dj.h"
void special(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {
		Rotate(0, -5);
	}
	else if (key == GLUT_KEY_RIGHT) {
		Rotate(0, 5);
	}
	else if (key == GLUT_KEY_UP) {
		Rotate(-5, 0);
	}
	else if (key == GLUT_KEY_DOWN) {
		Rotate(5, 0);
	}
}
