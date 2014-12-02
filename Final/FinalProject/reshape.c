/*
 * 
 */
#include "dj.h"
void reshape(int width, int height)
{
	//vaspect_ratio = (height > 0) ? (double)width/height : 1;

	// Reproject
	glViewport(0, 0, width, height);
	Project();
}
