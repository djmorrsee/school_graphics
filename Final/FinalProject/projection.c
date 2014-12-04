/*
 * 
 */
#include "dj.h"
void Project ()
{
	// Global Vars // 
	float fov = v_field_of_view;
	float asp = v_aspect_ratio;
	float clip = v_clipping_plane;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fov, asp, 1/clip, clip);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
