#include "djgraphics.h"

void drawLight(float r, float g, float b, vert pos, float amb, float spec, bool useSmooth) {
	glShadeModel(useSmooth ? GL_SMOOTH : GL_FLAT);

	float ambient[] = { amb, amb, amb, 1.0 };
	float diffuse[] = { r, g, b, 1.0 };
	float specular[] = { spec, spec, spec, 1 };
	
	float loc[] = { pos.x, pos.y, pos.z, 1 };
	
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	float m[] = {GL_TRUE};
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, m);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glEnable(GL_LIGHT0);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, loc);

}
