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
	GLuint rgb_buffer;
	GLuint tc_buffer;
	GLuint norm_buffer;
	
	GLuint texture_id;
};

dj_object load_object_from_obj(std::string filename);
dj_object create_object_from_parsed(); // Hard coded object creation

#endif /* SHADERS_H_ */
