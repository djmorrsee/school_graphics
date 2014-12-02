/*
 * mouse_move.c
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 */
#include "dj.h"

int last_x = 0;
int last_y = 0;
void mouse_move(int x, int y)
{
	printf("Mouse %d %d", x, y);
	Rotate(-(last_x - x), 0);
	last_x = x;
	glutPostRedisplay();

}
