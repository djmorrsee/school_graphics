/*
 * 
 */
#include "dj.h"
void Project ()
{
	// Global Vars // 
	float fov = vfield_of_view;
	float asp = vaspect_ratio;
	float clip = vclipping_plane;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fov, asp, 1/clip, clip);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
