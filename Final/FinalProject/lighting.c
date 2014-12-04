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
	glTranslatef(this_light.position.x, this_light.position.y, this_light.position.z);
	glutSolidSphere(.1, 10, 10);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_FLAT);

	float pos[3] = 	{ this_light.position.x, this_light.position.y, this_light.position.z };
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
	}

	glEnable(light_mac);
	glLightfv(light_mac, GL_DIFFUSE, dif);
	glLightfv(light_mac, GL_AMBIENT, amb);
	glLightfv(light_mac, GL_SPECULAR, spec);
	glLightfv(light_mac, GL_POSITION, pos);

	//	float amb[4] = { l.ambient.x, l.ambient.y, l.ambient.z, l.ambient.a };
	//	float diffuse[4] = { 1, 0, 0, 1 };
	//	float specular[4] = {l.specular.x, l.specular.y, l.specular.z, l.specular.a };
//		float position[3] = { l.position.x, l.position.y, -l.position.z };

//		glShadeModel(GL_FLAT);
//
//
//
//	    //  Translate intensity to color vectors
//	//    float Ambient[]   = { l.ambient.x, l.ambient.y, l.ambient.z, 1 };
//	    float Diffuse[]   = { 1, 0, 0, 1 };
//	//    float Specular[]  = {l.specular.x, l.specular.y, l.specular.z, l.specular.a };
//	//    //  Spotlight color and direction
//	//    float yellow[] = {1.0,1.0,1.0,1.0};
//	    //  Draw light position as ball (still no lighting here)
//	    //  OpenGL should normalize normal vectors
//	    //glEnable(GL_NORMALIZE);
//	    //  Enable lighting
//	    glEnable(GL_LIGHTING);
//	    //  Location of viewer for specular calculations
//	//    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);
//	    //  Two sided mode
//	//    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
//	    //  glColor sets ambient and diffuse color materials
//	//    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
//	    glEnable(GL_COLOR_MATERIAL);
//	    //  Set specular colors
//	//    glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
//	//    float shinyvec[]={1};
//	//    glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
//	    //  Enable light 0
//	    glEnable(GL_LIGHT0);
//	    //  Set ambient, diffuse, specular components and position of light 0
//	//    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
//	    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
//	    //glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
//	    glLightfv(GL_LIGHT0,GL_POSITION,position);


	//    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
	//    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	//    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);

}
