/*
 * objects.h
 *
 *  Created on: Dec 4, 2014
 *      Author: djmorrsee
 */

#ifndef OBJECTS_H_
#define OBJECTS_H_

struct dj_object {
	GLuint pos_buffer;
	GLuint col_buffer;
	GLuint tc_buffer;
	GLuint norm_buffer;
};

dj_object load_object(std::string filename);

#endif /* SHADERS_H_ */
