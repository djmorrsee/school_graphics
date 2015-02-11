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
	//~ if (button == GLUT_LEFT_BUTTON)
	//~ {
		//~ v_rotate_view = state == GLUT_DOWN ? true : false;
//~ 
		//~ last_x = x;
		//~ last_y = y;
	//~ }
}

void mouse_move(int x, int y)
{

	if (v_rotate_view) {

		float rotx = (float)(x - last_x) * dj_constants::c_rot_x_speed;
		float roty = (float)(last_y - y) * dj_constants::c_rot_y_speed;

		Rotate(-roty * 3, rotx);

		last_x = x;
		last_y = y;
	}

}
