/*
 * 
 */
#include "../dj.h"

void key(unsigned char ch, int x, int y) 
{
	//  Exit on ESC
	if (ch == 27)
		exit(0);

	if (ch == 'r') {
		v_clear_draw = true;
	}

	if (ch == 'c') {
		v_draw_color = (((v_draw_color + 1) % 3) + 1); // Increment, Constrict to [1,3] scale
	}
	
	//~ if (ch == 'w')
		//~ v_move_forward = true;
	//~ else if (ch == 's')
		//~ v_move_backward = true;
	//~ 
	//~ if (ch == 'a')
		//~ v_move_left = true;
	//~ else if (ch == 'd')
		//~ v_move_right = true;
		
	if (ch == 'w')
		Rotate(5, 0);
	else if (ch == 's')
		Rotate(-5, 0);
	
	if (ch == 'a')
		Rotate(0, 5);
	else if (ch == 'd')
		Rotate(0, -5);
}

void key_up(unsigned char ch, int x, int y)
{
	
	//~ if (ch == 'w')
		//~ v_move_forward = false;
	//~ else if (ch == 's')
		//~ v_move_backward = false;
	//~ 
	//~ if (ch == 'a')
		//~ v_move_left = false;
	//~ else if (ch == 'd')
		//~ v_move_right = false;
}
