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
	Rotate(-(last_x - x), -(last_y - y));
	last_x = x;
	last_y = y;
	glutPostRedisplay();

}
