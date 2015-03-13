/*
 * mouse_move.c
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 */
#include "../../dj.h"
#include <stdbool.h>

int last_x, last_y;
void mouse_click(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN) {
			v_cursor_down = true;
			mouse_move(x, y);
		} else if (state == GLUT_UP) {
			v_cursor_down = false;
		}
	}
}

void mouse_move(int x, int y)
{
	v_cursor_x = x;
	v_cursor_y = y;
}
