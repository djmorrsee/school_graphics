/*
 * Universal Projection Function
 */
#include "djgraphics.h"

void GetDefaultProjectionValues (float* fov, float* dim, float* asp) {
	*fov = 45;
	*dim = 15;
	*asp = 1;
}

void Project (float fov, float dim, float asp, bool usePersp) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(usePersp) {
		gluPerspective(fov, asp, dim/16, 16 * dim);
	} else {
		glOrtho(-asp * dim, asp * dim, -dim, dim, -dim * 2, dim * 2);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
