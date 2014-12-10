/*
 * shaders.c
 *
 *  Created on: Dec 4, 2014
 *      Author: djmorrsee
 */

#include "dj.h"
#include <sys/stat.h>
#include <unistd.h>
GLuint vertex_shaders[8];
GLuint fragment_shaders[8];
GLuint shader_programs[8];

int file_exist (char *filename)
{
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}

char *readShaderFile(char *filename)
{
	FILE *fp;
	char *content = NULL;
	int count = 0;
	if (filename != NULL)
	{
		fp = fopen(filename, "rt");
		if(fp != NULL)
		{

			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0)
			{
				content = (char *)malloc(sizeof(char) * (count + 1));
				count = fread (content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}
int writeTextFile(char *filename, char *s)
{
	FILE *fp;
	int status = 0;

	if (filename != NULL)
	{
		fp = fopen(filename, "w");
		if(fwrite(s, sizeof(char),strlen(s), fp) == strlen(s))
			status = 1;
		fclose(fp);
	}
	return status;
}


/*
 *  Print Shader Log
 */
void PrintShaderLog(int obj,char* file)
{
	GLint status;
	glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		GLint logLength;
		glGetShaderiv(obj,GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			GLchar *log = (GLchar *)malloc(logLength);
			glGetShaderInfoLog(obj, logLength, &logLength, log);
			printf("Shader Log: \n%s\n", log);
		}
	}
}

/*
 *  Print Program Log
 */
void PrintProgramLog(int obj)
{
   int len=0;
   glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&len);
   if (len>1)
   {
      int n=0;
      char* buffer = (char *)malloc(len);
      if (!buffer) Fatal("Cannot allocate %d bytes of text for program log\n",len);
      glGetProgramInfoLog(obj,len,&n,buffer);
      fprintf(stderr,"%s\n",buffer);
   }
   glGetProgramiv(obj,GL_LINK_STATUS,&len);
   if (!len) {
	   Fatal("Error linking program\n");
   }
}

void load_shaders ()
{


	char *vs = NULL;
	char *fs = NULL;
	int i;

	for(i = 0; i < 2; ++i)
	{

		char vn[16];
		char fn[16];

		sprintf(vn, "shaders/%d.vert", i);
		sprintf(fn, "shaders/%d.frag", i);

		shader_programs[i] = glCreateProgram();

		if (file_exist(vn)) {

			vs = readShaderFile(vn);
			const char * vv = vs;

			vertex_shaders[i] = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex_shaders[i], 1, &vv, NULL);
			glCompileShader(vertex_shaders[i]);

			PrintShaderLog(vertex_shaders[i], vn);

			glAttachShader(shader_programs[i], vertex_shaders[i]);

		}

		if(file_exist(fn)) {

			fs = readShaderFile(fn);
			const char * fv = fs;

			fragment_shaders[i] = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment_shaders[i], 1, &fv, NULL);
			glCompileShader(fragment_shaders[i]);

			PrintShaderLog(fragment_shaders[i], fn);

			glAttachShader(shader_programs[i], fragment_shaders[i]);
		}
		glLinkProgram(shader_programs[i]);
		PrintProgramLog(shader_programs[i]);
	}
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
