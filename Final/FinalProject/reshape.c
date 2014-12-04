/*
 * 
 */
#include "dj.h"
void reshape(int width, int height)
{
	v_aspect_ratio = (height > 0) ? (double)width/height : 1;
	v_window_width = width;
	v_window_height = height;
	// Reproject
	glViewport(0, 0, width, height);
	glutPostRedisplay();
}
