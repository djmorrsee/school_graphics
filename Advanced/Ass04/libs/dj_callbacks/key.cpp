/*
 * 
 */
#include "../../dj.h"

void key(unsigned char ch, int x, int y) 
{
	//  Exit on ESC
	if (ch == 27)
		exit(0);

	if(ch == 'w')
		v_x_persp_rot += 1;
	if (ch == 's')
		v_x_persp_rot -= 1;
	if (ch == 'a')
		v_y_persp_rot += 1;
	if (ch == 'd')
		v_y_persp_rot -= 1;

	if(ch == 'p')
		v_shader_mode = (v_shader_mode + 1) % dj_constants::c_num_shaders;

	if (ch == 'l')
		v_use_perspective = !v_use_perspective;

}

void key_up(unsigned char ch, int x, int y)
{
	if(ch == 'w')
		v_move_forward = false;
	else if (ch == 's')
		v_move_backward = false;
	else if (ch == 'a')
		v_move_left = false;
	else if (ch == 'd')
		v_move_right = false;

}
