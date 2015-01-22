/*
 * shaders.h
 *
 *  Created on: Dec 4, 2014
 *      Author: djmorrsee
 */

#ifndef SHADERS_H_
#define SHADERS_H_

// Load All Shaders for Program
void load_shaders();

// Select the Shader to use
void use_shader(int id);

// Get a friendly name for the current shader
char* ShaderName();

#endif /* SHADERS_H_ */
