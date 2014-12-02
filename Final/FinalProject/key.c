/*
 * 
 */
#include "dj.h"
void key(unsigned char ch, int x, int y) 
{
	//  Exit on ESC
	if (ch == 27)
		exit(0);

	if(ch == 'w')
		Move(forward);
	else if (ch == 's')
		Move(backward);
	else if (ch == 'a')
		Move(left);
	else if (ch == 'd')
		Move(right);



	glutPostRedisplay();
}
