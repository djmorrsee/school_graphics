/* 
 * Axis Drawing Function
 */
#include "djgraphics.h"

void DrawAxes(float len) 
{
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3d(-len, 0, 0);
	glVertex3d(len, 0, 0);
	glVertex3d(0, -len, 0);
	glVertex3d(0, len, 0);
	glVertex3d(0, 0, -len);
	glVertex3d(0, 0, len);
	glEnd();
	glPopMatrix();
}
