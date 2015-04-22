/*
 * 
 */
#include "../dj.h"
void reshape(int width, int height)
{
	v_aspect_ratio = (height > 0) ? (double)width/height : 1;
	v_window_size.x = width;
	v_window_size.y = height;
	// Reproject
	glViewport(0, 0, width, height);
	
}
