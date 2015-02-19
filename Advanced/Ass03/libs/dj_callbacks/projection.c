/*
 * 
 */
#include "../../dj.h"
void Project ()
{
	// Global Vars // 
	float fov = v_field_of_view;
	float asp = v_aspect_ratio;
	float clip = v_clipping_plane;
	float dim = v_dim;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
   	if (v_use_perspective)
     	 	gluPerspective(fov,asp,1.0/clip, clip);
   	else
		glOrtho(-asp*dim,asp*dim,-dim,+dim,-dim,+dim);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
