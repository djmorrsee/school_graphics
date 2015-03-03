/*
 * objects.cpp
 * 
 * Handles various routes to generating object buffers
 * 
 */

#include "../../dj.h"
#include "objects.h"

dj_object load_object(std::string filename) {
	dj_object new_obj;
	
	glGenBuffers(1, &new_obj.pos_buffer);
	glGenBuffers(1, &new_obj.col_buffer);
	glGenBuffers(1, &new_obj.tc_buffer);
	glGenBuffers(1, &new_obj.norm_buffer);
	
	return new_obj;
}
