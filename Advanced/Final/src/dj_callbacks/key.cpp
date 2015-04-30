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
		v_chunk_type += 1;
		v_chunk_type %= 3;
	}
	
	if (ch == 'a') {
		Rotate(0, -5);
	}
	else if (ch == 'd') {
		Rotate(0, 5);
	}
	else if (ch == 'w') {
		Rotate(-5, 0);
	}
	else if (ch == 's') {
		Rotate(5, 0);
	}
		
}

void key_up(unsigned char ch, int x, int y)
{
	

}
