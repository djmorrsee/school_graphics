/*
 * lighting.c
 *
 *  Created on: Dec 4, 2014
 *      Author: djmorrsee
 */

#include "dj.h"

void set_light(int num, vector3 pos, vector4 rgb)
{
	lights[num].position = pos;
	lights[num].diffuse = rgb;
}

void draw_light (int num)
{
	// num < 8

	light this_light = lights[num];

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor4f(this_light.diffuse.x, this_light.diffuse.y, this_light.diffuse.z, this_light.diffuse.a);
	glTranslatef(this_light.position.x, this_light.position.y, this_light.position.z);
	glutSolidSphere(.1, 10, 10);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);

	float pos[4] = 	{ this_light.position.x, this_light.position.y, this_light.position.z, 1 };
	float dif[4] = 	{ this_light.diffuse.x, this_light.diffuse.y, this_light.diffuse.z, this_light.diffuse.a };
	float spec[4] = { this_light.specular.x, this_light.specular.y, this_light.specular.z, this_light.specular.a };
	float amb[4] = 	{ this_light.ambient.x, this_light.ambient.y, this_light.ambient.z, this_light.ambient.a };

	int light_mac;
	switch(num)
	{
	case 0:
		light_mac = GL_LIGHT0;
		break;
	case 1:
		light_mac = GL_LIGHT1;
		break;
	case 2:
		light_mac = GL_LIGHT2;
		break;
	case 3:
		light_mac = GL_LIGHT3;
		break;
	case 4:
		light_mac = GL_LIGHT4;
		break;
	case 5:
		light_mac = GL_LIGHT5;
		break;
	case 6:
		light_mac = GL_LIGHT6;
		break;
	case 7:
		light_mac = GL_LIGHT7;
		break;
	default:
		light_mac = 0;
	}

	glEnable(light_mac);
	glLightfv(light_mac, GL_DIFFUSE, dif);
	glLightfv(light_mac, GL_AMBIENT, amb);
	glLightfv(light_mac, GL_SPECULAR, spec);
	glLightfv(light_mac, GL_POSITION, pos);

	glLightf(light_mac, GL_CONSTANT_ATTENUATION, 2.0);
	glLightf(light_mac, GL_LINEAR_ATTENUATION, 1.0);
	glLightf(light_mac, GL_QUADRATIC_ATTENUATION, 0.5);

}
