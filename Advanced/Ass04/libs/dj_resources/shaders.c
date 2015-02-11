/*
 * shaders.c
 *
 *  Created on: Dec 4, 2014
 *      Author: djmorrsee
 */

#include "../../dj.h"
#include <sys/stat.h>
#include <unistd.h>

GLuint shader_programs[8];

void load_shaders ()
{
	shader_programs[0] = 0; // Fixed
	shader_programs[1] = CreateShaderProg("libs/dj_resources/shaders/disp.vert", NULL);
}

char* ShaderName()
{
	switch (v_shader_mode)
	{
	case 0:
		return "Fixed";
		break;
	case 1:
		return "Displacement";
		break;
	default:
		return "NaS";

	}
}
