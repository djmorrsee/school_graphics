/*
 * shaders.c
 *
 *  Created on: Dec 4, 2014
 *      Author: djmorrsee
 */

#include "../dj.h"
#include <sys/stat.h>
#include <unistd.h>

GLuint shader_programs[8];

void load_shaders ()
{
	

}

void use_shader(int id)
{
	if (id)
	{
		glUseProgram(shader_programs[id-1]);
	} else {
		glUseProgram(0);
	}

}


char* ShaderName()
{
	switch (v_shader_mode)
	{
	case 0:
		return "Fixed";
		break;
	case 1:
		return "\"Toon\"";
		break;
	case 2:
		return "Per Pixel";
		break;
	default:
		return "NaS";

	}
}
