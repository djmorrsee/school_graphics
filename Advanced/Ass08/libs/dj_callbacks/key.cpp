/*
 * 
 */
#include "../../dj.h"

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
	
}

void key_up(unsigned char ch, int x, int y)
{
	
}
