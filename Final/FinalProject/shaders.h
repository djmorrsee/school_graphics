/*
 * shaders.h
 *
 *  Created on: Dec 4, 2014
 *      Author: djmorrsee
 */

#ifndef SHADERS_H_
#define SHADERS_H_

char *readShaderFile(char *filename);
int writeTextFile(char *filename, char *s);

void load_shaders();
void use_shader(int id);
char* ShaderName();

#endif /* SHADERS_H_ */
