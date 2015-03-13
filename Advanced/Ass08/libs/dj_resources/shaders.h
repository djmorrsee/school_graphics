/*
 * shaders.h
 *
 *  Created on: Dec 4, 2014
 *      Author: djmorrsee
 */

#ifndef SHADERS_H_
#define SHADERS_H_

int load_shader(const char* vertname, const char* fragname);

// Get a friendly name for the current shader
std::string ShaderName();

#endif /* SHADERS_H_ */
